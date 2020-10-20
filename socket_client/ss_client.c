#include "ss_client_private.h"
#include "socket_client_api.h"
#include "ss_client_friend.h"
#include "ss_version.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <json-c/json.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

/**
 * This constant can be made non-zero to print out received data
 */
#ifndef SCA_DEBUG_RECEIVED_DATA
# define SCA_DEBUG_RECEIVED_DATA (0)
#endif

/**
 * This constant can be made non-zero to print out "payload" field as a string
 */
#ifndef SCA_DEBUG_PAYLOAD_AS_STRING
# define SCA_DEBUG_PAYLOAD_AS_STRING (0)
#endif

/**
 * This constant can be made non-zero to print out the raw bytes read from a socket
 */
#ifndef SCA_DEBUG_RAW_BYTES
# define SCA_DEBUG_RAW_BYTES (0)
#endif

/**
 * Timeout waiting for initial connection attempt to complete.
 */
#ifndef SCA_INITIAL_CONNECT_TIMEOUT_MS
# define SCA_INITIAL_CONNECT_TIMEOUT_MS 10000
#endif

/**
 * Timeout for poll call that waits for input data.
 */
#ifndef SCA_POLL_TIMEOUT_MS
# define SCA_POLL_TIMEOUT_MS 5000
#endif

/**
 * Timeout for client thread to exit on disconnect
 */
#ifndef SCA_CLIENT_THREAD_JOIN_TIMEOUT_MS
#  define SCA_CLIENT_THREAD_JOIN_TIMEOUT_MS 10000
#endif
/**
 * Timeout for Server to close connection
 */
#ifndef SS_DISCONNECT_TIMEOUT_MS
   #define SS_DISCONNECT_TIMEOUT_MS 5000
#endif

/**
 * Timeout to retry to connect
 */
#ifndef SCA_CLIENT_RECONNECT_TIMEOUT_MS
   #define SCA_CLIENT_RECONNECT_TIMEOUT_MS 1000
#endif

/**
 * Maximum number of times the receive logic is allowed to timeout waiting for
 * data before the client logic determines it is no longer connected to the
 * server and disconnects.
 */
#ifndef SCA_MAX_NUM_POLL_TIMEOUTS
# define SCA_MAX_NUM_POLL_TIMEOUTS 3
#endif

/**
 * This constant is the maximum size of a static (that is, non-malloc'ed) payload for a message,
 * calculated from SCA_MAX_STATIC_MESSAGE_SIZE
 */
#define SCA_MAX_STATIC_PAYLOAD_SIZE (SCA_MAX_STATIC_MESSAGE_SIZE - sizeof(SS_Message_Header_T))

/**
 * Default SS_HELLO message payload.
 */
#define SS_CLIENT_DEFAULT_HELLO "{ \"lib_version\": \"" SS_VERSION "\", \"origin\": \"" SS_ORIGIN "\" }"

/**
 * Maximum number of characters to report in hostname.
 */
#define SS_MAX_HOSTNAME 17

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

static void* Client_Thread(void* user_data);
static void Configure_Socket(SCA_Client_Instance_T* instance);
static void Establish_Connection(SCA_Client_Instance_T* instance);
static ssize_t Read_From_Socket(SCA_Client_Instance_T* instance, char* buffer, size_t num_bytes_to_read);
static void Notify_Client_Of_Connection_Info(SCA_Client_Instance_T * instance, SCA_Connection_State_T connection_state,
   SCA_Connection_Error_T connection_error);
static void Receive_From_Client(SCA_Client_Instance_T* instance);
static void SIGPIPE_Handler(int signo);
static void Shutdown(SCA_Client_Instance_T* instance);
static void Wait_For_Receive_Data(SCA_Client_Instance_T* instance);
static int Write_Message(SCA_Client_Instance_T* instance, SS_Message_Header_T const * wr_hdr, void const * const payload,
   size_t payload_size);

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/

/**
 * Implements the receive thread for the SSC.
 *
 * @param user_data SCA_Client_Instance_T pointer for this SSC.
 */
static void* Client_Thread(void* user_data)
{
   bool_t signalled_start = false;
   sigset_t set;
   struct sigaction act;
   SCA_Client_Instance_T* instance = (SCA_Client_Instance_T*) user_data;
   int err;
   uint32_t disconnect_sleep = 0;

   SCA_DEBUG_0(">> Client_Thread() - enter");

#ifdef PR_SET_NAME
   /* set thread name */
   prctl(PR_SET_NAME, "SCA Listen");
#endif
   /* Catch SIGPIPE in case the SocketServer unexpectedly dies */
   sigemptyset(&set);
   act.sa_flags = 0;
   act.sa_mask = set;
   act.sa_handler = &SIGPIPE_Handler;

   if (sigaction(SIGPIPE, &act, NULL) < 0)
   {
      SCA_ERR_0(
         "Error: Failed to register signal handler for SIGPIPE. Any SIGPIPE signal will be missed. Operation may be encumbered");
   }

   if (NULL == inet_ntop(AF_INET, &instance->socket_adr.sin_addr, instance->inet_addr_string, sizeof(instance->inet_addr_string)))
   {
      SCA_ERR_0("inet_ntop() Unable to create a printable ip address");
   }

   while (SCA_DISCONNECTED != instance->connection_state)
   {
      /*
       * Make sure client is connected
       */
      while ((instance->connect_result < 0) && (SCA_CONNECTING == instance->connection_state))
      {
         Establish_Connection(instance);
         if (!signalled_start)
         { /*
          * Wait until after the 1st connection attempt before signalling (allowing
          * SCA_Connect() to continue). This means that a lot of the time, a
          * connection will have been established by the time SCA_Connect() returns.
          */
            sem_post(&instance->start_stop_sem);
            signalled_start = true;
         }
         if (instance->connect_result < 0)
         {
            usleep(1000 * SCA_CLIENT_RECONNECT_TIMEOUT_MS);
         }
         else
         {
            if(SCA_Is_Connected(instance))
            {
               sem_post(&instance->connect_semaphore);
            }
            SCA_DEBUG_1("Client_Thread(): state = %s", Connection_State_To_String(instance->connection_state));
         }
      }
      /*
       * Receive data from the client
       */
      if ((instance->connect_result >= 0)
         && ((SCA_CONNECTED == instance->connection_state) || (SCA_DISCONNECTING == instance->connection_state)))
      {
         Wait_For_Receive_Data(instance);

         if (SCA_Is_Connected(instance))
         {
            Receive_From_Client(instance);

            if (!SCA_Is_Connected(instance))
            {
               sleep(1); /* If we got disconnected, wait 1 sec. before re-connecting */
            }
         }
      }
   }
   /*
    * Wait for Server to close the connection so program exit
    * will not shutdown the socket and cause faults on server.
    * recv will return 0 once the socket has been properly shutdown.
    */
   //TODO
   #if 0
   if(-1 != instance->socket_ref)
   {
      if(instance->is_ssl_client)
      {
         err = sca_Read_Socket_SSL(instance,instance->rd_buffer,instance->rd_buffer_size);
      }
      else
      {
         err = recv(instance->socket_ref,instance->rd_buffer,instance->rd_buffer_size, MSG_DONTWAIT);
      }
      while(disconnect_sleep < SS_DISCONNECT_TIMEOUT_MS && 0 != err)
      {
         usleep(100 * 1000);
         disconnect_sleep += 100;
         if(instance->is_ssl_client)
         {
            err = sca_Read_Socket_SSL(instance,instance->rd_buffer,instance->rd_buffer_size);
         }
         else
         {
            err = recv(instance->socket_ref,instance->rd_buffer,instance->rd_buffer_size, MSG_DONTWAIT);
         }
      }
      if(0 != err)
      {
         //Tr_Fault_1("Timeout waiting for server to disconnect socket for %s",instance->uid_str);
      }
   }
   #endif

   /*
    * Signal that we're shutting down so that SCA_Disconnect() can continue.
    */
   err = sem_post(&instance->start_stop_sem);
   if (err != 0)
   {
      SCA_ERR_1("sem_post failed: %s", strerror(errno));
   }
   else
   {
      SCA_DEBUG_0("disconnected, exiting Client_Thread()");
   }
   SCA_DEBUG_0("<< Client_Thread() - exit");

   return NULL;
}

/**
 * Configures a standard (non-secure) socket.
 *
 * @param instance Pointer to client instance data.
 */
static void Configure_Socket(SCA_Client_Instance_T* instance)
{
   int sock_opt = 1;

   if (setsockopt(instance->socket_ref, IPPROTO_TCP, TCP_NODELAY, &sock_opt, sizeof sock_opt) < 0)
   {
      SCA_ERR_1("Could not set TCP_NODELAY: %s", strerror(errno));
   }
}

/**
 * Attempts to establish a connection to the SocketServer.
 *
 * @param instance  Pointer to client instance data.
 */
static void Establish_Connection(SCA_Client_Instance_T *instance)
{
    int connect_result = -1;
    /* Open a socket */
    instance->socket_ref = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* If a socket could not be opened, try again later */
    if (instance->socket_ref < 0)
    {
        SCA_ERR_1("could not create socket: '%s'", strerror(errno));
    }
    /* Otherwise, a socket was successfully opened... */
    else
    {
        /*
       * Store the connection result locally so SCA_Is_Connected does not
       * report true when SSL is not really ready yet.  By triggering "connected"
       * before SSL is done SSL connections can fail if another thread attempts
       * to write to the socket during the SSL handshake.  Then set the instance
       * after SSL_Connect for secure connections and if not secure then set it.
       */
        connect_result = connect(instance->socket_ref, (struct sockaddr *)(&instance->socket_adr),
                                 sizeof(struct sockaddr_in));

        /* If a connection could not be made, try again later */
        if (connect_result < 0)
        {
            SCA_DEBUG_1("could not open connection: '%s'", strerror(errno));
            instance->connect_result = connect_result;
            shutdown(instance->socket_ref, SHUT_RDWR);
            close(instance->socket_ref);
            instance->socket_ref = -1;
            Notify_Client_Of_Connection_Info(instance, SCA_CONNECTING, SCA_CONNECTION_RETRY);
        }
        else
        {
           printf("Establish_Connection: '%s'\n", "Establish_Connection");
            if (instance->is_ssl_client)
            {
                //sca_Configure_SSL_Socket(instance);
                if (-1 == instance->socket_ref)
                {
                    instance->connect_result = -1;
                    Notify_Client_Of_Connection_Info(instance, SCA_CONNECTING, SCA_CONNECTION_RETRY);
                }
                else
                {
                    instance->connect_result = connect_result;
                }
            }
            else
            {
                instance->connect_result = connect_result;
                Configure_Socket(instance);
            }

            if (instance->socket_ref != -1)
            {
                //Setup_Initial_Connection(instance);
            }
        }
    }
}

/**
 * This function reads up to num_bytes_to_read bytes from the socket, and
 * fills "buffer" with the bytes that were read.
 *
 * @return The number of bytes that were read
 *
 * @param instance  Pointer to client instance data.
 * @param buffer Location to which data is written.
 * @param num_bytes_to_read Number of bytes to be read.
 */
static ssize_t Read_From_Socket(SCA_Client_Instance_T* instance, char* buffer, size_t num_bytes_to_read)
{
   /* Number of bytes read by recv() below */
   ssize_t rcvd_size = -1;

   /* May receive partial messages, this keeps track of where we have "filled the buffer to" so far */
   char* read_to_buffer = buffer;

   /* May receive partial messages, this keeps track of how many bytes remain to be read */
   size_t bytes_remaining = num_bytes_to_read;

   /* While more bytes to read... */
   while (bytes_remaining > 0)
   {
      int recv_error;

      /* Read a buffer-full of data from the socket */
      SCA_DEBUG_0("Read_From_Socket: calling recv");
      if(instance->is_ssl_client)
      {
          //rcvd_size = sca_Read_Socket_SSL(instance,read_to_buffer, bytes_remaining);
      }
      else
      {
          rcvd_size = recv(instance->socket_ref, read_to_buffer, bytes_remaining, 0);
      }
      SCA_DEBUG_1("Read_From_Socket: returned from recv with %d bytes", (int )rcvd_size);
      recv_error = errno;

      if (rcvd_size > 0)
      {
#if SCA_DEBUG_RAW_BYTES
         {
            int i = 0;

            printf("[%d] rcvd_size=%d\n\n        [%d] ", instance->socket_ref, rcvd_size, instance->socket_ref);

            for(i=1; i<=rcvd_size; i++)
            {
               printf("%4d: 0x%02X ", i - 1, (int)((unsigned char)read_to_buffer[i - 1]));

               if(i != rcvd_size &&
                  0 == i % 4)
               {
                  printf("\n        [%d] ", instance->socket_ref);
               }
            }

            printf("\n\n");
         }
#endif
         /* Account for the bytes read, and also "read to buffer pointer" */
         bytes_remaining = bytes_remaining - rcvd_size;
         read_to_buffer = read_to_buffer + rcvd_size;
      }
      else if (SCA_CONNECTED == instance->connection_state)
      { /*
       * We're supposed to be connected and some sort of abnormal condition
       * has occurred.
       */
         if (0 == rcvd_size)
         {
            SCA_ERR_0(
               "Read_From_Socket : Connection to SocketServer terminated unexpectedly.\n" "Is the SocketServer still running? Is the cable disconnected?\n");

            Notify_Client_Of_Connection_Info(instance, SCA_DISCONNECTED, SCA_READV_0_BYTES);

            sca_Disconnect_On_Err(instance);
            break;
         }
         else if ((!instance->is_ssl_client) && (EINTR == recv_error))
         {
            /* just try again if interrupted by a signal */
            SCA_DEBUG_0("recv() call returned due to EINTR - retrying");
         }
         else
         {
            /* For any other error print the error string and disconnect */
            SCA_ERR_2("Client failed to read from socket. Error Code: %s - %d", strerror(recv_error), recv_error);

            Notify_Client_Of_Connection_Info(instance, SCA_DISCONNECTED, SCA_UNKNOWN_READV_ERROR);

            sca_Disconnect_On_Err(instance);
            break; /* out of while */
         }
      }
      else /* We're supposed to be disconnected. */
      {
         SCA_Lock_Mutex(instance->instance_mutex);
         /*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
         instance->connection_state = SCA_DISCONNECTED; /* Expected disconnect. Do not attempt reconnect */
         SCA_DEBUG_0("connection_state = SCA_DISCONNECTED");
         /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
         SCA_Unlock_Mutex(instance->instance_mutex);
         break;
      }
   } /* while (bytes_remaining > 0) */

   return (num_bytes_to_read - bytes_remaining);
}

/**
 * Receives messages from SocketServer, checks for errors, handles "standard"
 * messages (like SOH), and calls the client's callback function to handle
 * non-standard messages.
 *
 * @param instance  Pointer to client instance data.
 */
static void Receive_From_Client(SCA_Client_Instance_T* instance)
{
   /* Try to read from the socket */
   ssize_t rcvd_size = Read_From_Socket(instance, instance->rd_buffer, sizeof(SS_Message_Header_T));

   if (rcvd_size > 0 && SCA_Is_Connected(instance))
   {
      /* Message will be parsed piece-by-piece into the following variables */
      uint32_t destination = 0UL;
      uint32_t code = 0UL;
      uint32_t data = 0UL;
      uint32_t payload_size = 0UL;
      char const* payload = NULL;
      uint32_t* u32_values = (uint32_t*) instance->rd_buffer;

      /* Restore the endian-ness after receiving via network transmission */
      u32_values[0] = ntohl(u32_values[0]);
      u32_values[1] = ntohl(u32_values[1]);
      u32_values[2] = ntohl(u32_values[2]);
      u32_values[3] = ntohl(u32_values[3]);

#if SCA_DEBUG_RECEIVED_DATA
      SCA_DEBUG_2("[%d] rcvd_size=%d", instance->socket_ref, rcvd_size);
#endif

      destination = u32_values[0];
      code = u32_values[1];
      (void) code; /* get rid of "set but not used compiler warning */
      data = u32_values[2];
      (void) data; /* get rid of "set but not used compiler warning */
      payload_size = u32_values[3];

#if SCA_DEBUG_RECEIVED_DATA
      SCA_DEBUG_1(" destination:0x%08X", destination);
      SCA_DEBUG_1("        code:0x%08X", code);
      SCA_DEBUG_1("        data:0x%08X", data);
      SCA_DEBUG_1("payload_size:%u", payload_size);
#endif

      /* If there is a payload, read the payload */
      if (payload_size > 0)
      {
         uint32_t total_msg_size = payload_size + sizeof(SS_Message_Header_T);
         /*
          * If buffer won't hold the message, realloc it to the next
          * SCA_INITIAL_MESSAGE_SIZE byte boundary bigger.
          * Add an extra byte to add a NULL termination 1 byte after payload_size
          */
         if ((total_msg_size+1) > instance->rd_buffer_size)
         {
            size_t new_size = (((total_msg_size+1) / SCA_INITIAL_MESSAGE_SIZE) + 1) * SCA_INITIAL_MESSAGE_SIZE;
            char * new_buffer = realloc(instance->rd_buffer, new_size);
            if (new_buffer != NULL)
            {
               instance->rd_buffer_size = new_size;
               instance->rd_buffer = new_buffer;
            }
            else
            {
               SCA_ERR_0("Failed to reallocate receive buffer. Disconnecting.");
               sca_Disconnect_On_Err(instance);
               /*****/
               return; /* Can't process this (or any) message any more. */
               /*****/
            }
         }

         rcvd_size = Read_From_Socket(instance, &instance->rd_buffer[sizeof(SS_Message_Header_T)], payload_size);
         /*
          * NULL terminate just in case payload_size was incorrect, if it was
          * correct string will be double NULL terminated.
          */
         instance->rd_buffer[sizeof(SS_Message_Header_T) + payload_size] = 0;

         /* Get a pointer to the payload */
         payload = &instance->rd_buffer[sizeof(SS_Message_Header_T)];

#if SCA_DEBUG_PAYLOAD_AS_STRING
         SCA_DEBUG_1("      payload:'%s'", payload);
#endif
      }
#if 0 // TODO
      if (!sca_Process_Local_Message(instance, destination, code, data, payload_size, payload) && (instance->callback != NULL))
      {
         if (NULL != instance->context)
         {
            SCA_Message_Context_Callback_T cb = instance->callback;
            cb((SCA_Message_T*) (instance->rd_buffer + sizeof(destination)), instance->context);
         }
         else
         {
            SCA_Message_Callback_T cb = instance->callback;
            cb((SCA_Message_T*) (instance->rd_buffer + sizeof(destination)));
         }
      }
#endif
   }
   /* !!! WARNING: Early return in function body !!! */
}

/*
 * Please refer to ss_client_private.h for the description.
 */
void sca_Disconnect_On_Err(SCA_Client_Instance_T* instance)
{
   SCA_Lock_Mutex(instance->instance_mutex);
   /*vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
   Shutdown(instance);
   if (SCA_CONNECTED == instance->connection_state)
   {
      /* Will attempt to re-connect until SCA_Disconnect is called. */
      instance->connection_state = SCA_CONNECTING;
      SCA_DEBUG_0("connection_state = SCA_CONNECTING");
   }
   /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
   SCA_Unlock_Mutex(instance->instance_mutex);
}

/*
 * Please refer to ss_client_private.h for the description.
 */
bool_t sca_Instance_Is_Valid_Func(char const *func_name, SCA_Client_Instance_T* instance)
{
   bool_t result = false;

   if (NULL == instance)
   {
      //SCA_ERR_NULL("%s was passed a NULL instance.", func_name);
   }
   else if (instance->valid_pattern != SCA_CONTEXT_PATTERN)
   {
      //SCA_ERR_1("%s was passed an instance that appears to not have been initialized.", func_name);
   }
   else
   {
      result = true;
   }

   return result;
}

/*
 * Please refer to ss_client_private.h for the description.
 */
int sca_Send_Message(SCA_Client_Instance_T* instance, SCA_Socket_Client_Unique_ID_T destination, uint32_t code, uint32_t data,
   void const * const payload, size_t payload_size)
{
   int result = -1;

   if (!sca_Instance_Is_Valid(instance))
   {
      /* ignore */
   }
   else
   {
      SCA_Lock_Mutex(instance->send_lock);
      /*vvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
      /* Messages can only be sent if we are in the "connected" state */
      if (!SCA_Is_Connected(instance))
      {
         SCA_ERR_2("not connected: code=0x%08X data=0x%08X", code, data);
      }
      else
      {
         SS_Message_Header_T wr_hdr;

         /* Build the message header (in network order) from the passed-in args. */
         wr_hdr.destination = htonl(destination);
         wr_hdr.code = htonl(code);
         wr_hdr.data = htonl(data);
         wr_hdr.payload_size = htonl(payload_size);

         if (instance->is_ssl_client)
         {
            // result = sca_Write_Message_SSL(instance, &wr_hdr, payload, payload_size);
         }
         else
         {
            result = Write_Message(instance, &wr_hdr, payload, payload_size);
         }
      }
      /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
      SCA_Unlock_Mutex(instance->send_lock);
   }

   return result;
}

static void Notify_Client_Of_Connection_Info(SCA_Client_Instance_T * instance, SCA_Connection_State_T connection_state,
   SCA_Connection_Error_T connection_error)
{
   if (NULL != instance->connection_info_callback)
   {
      SCA_Connection_Info_Callback_T cb = instance->connection_info_callback;

      cb(instance, connection_state, connection_error);
   }
}

/*
 * Please refer to socket_client_api.h for the description.
 */
char const *SCA_Get_Version(void)
{
   return SS_VERSION " (" SS_ORIGIN ")";
}

/*
 * Please refer to socket_client_api.h for the description.
 */
SCA_Socket_Client_Unique_ID_T SCA_Convert_String_To_UID(char const *const unique_fourcc_name)
{
    /* Default to invalid uid */
    SCA_Socket_Client_Unique_ID_T return_value = /*SS_BROADCAST_DESTINATION*/0xFFFFFFFF;

    /* If a valid string was passed-in... */
    if (NULL != unique_fourcc_name)
    {
        /* Convert the first 4 characters of the string using the SCA_FOURCC_TO_UID() macro */
        //return_value = SCA_FOURCC_TO_UID(unique_fourcc_name[0], unique_fourcc_name[1], unique_fourcc_name[2], unique_fourcc_name[3]);
    }

    return return_value;
}


/*
 * Please refer to socket_client_api.h for the description.
 */
void SCA_Set_UID(SCA_Client_Instance_T* instance, SCA_Socket_Client_Unique_ID_T unique_id)
{
   if (sca_Instance_Is_Valid(instance) && (unique_id != instance->uid))
   {
      if (instance->uid != 0)
      {
         /* Reject attempts to change the UID once it is set. */
         char local_uid_str[sizeof(unique_id) + 1] =
            { 0 };
         SCA_UID_To_String(unique_id, local_uid_str, sizeof(local_uid_str));
         SCA_ERR_1("Rejecting attempt to change UID to %s", local_uid_str);
      }
      else
      {
         ssize_t path_size;

         instance->uid = unique_id;
         SCA_UID_To_String(unique_id, instance->uid_str, sizeof(instance->uid_str));

         path_size = snprintf(NULL, 0, "%s%s", SS_DBC_PATH, instance->uid_str);
         if (path_size > 0)
         {
            ++path_size; /* account for NUL terminator */
            instance->dbg_ctrl_path = malloc(path_size);
            if (instance->dbg_ctrl_path != NULL)
            {
               snprintf(instance->dbg_ctrl_path, path_size, "%s%s", SS_DBC_PATH, instance->uid_str);
               SCA_DEBUG_1("Attempting to read dbg_ctrl levels from '%s'", instance->dbg_ctrl_path);
               //Tr_Read_Trace_Levels(instance->dbg_ctrl_path);
            }
         }
         else
         {
            SCA_ERR_0("Could not form name for dbg_trace persistent path");
         }
      }
   }
}

/*
 * Please refer to socket_client_api.h for the description.
 */
void SCA_UID_To_String(uint32_t uid, char *buf, size_t buf_size)
{
   if (buf != NULL)
   {
      int c1 = (uid >> 24) & 0xff;
      int c2 = (uid >> 16) & 0xff;
      int c3 = (uid >> 8) & 0xff;
      int c4 = uid & 0xff;

      snprintf(buf, buf_size, "%c%c%c%c", (isprint(c1) ? c1 : '.'), (isprint(c2) ? c2 : '.'), (isprint(c3) ? c3 : '.'),
         (isprint(c4) ? c4 : '.'));
   }
}

/*
 * Please refer to socket_client_api.h for the description.
 */
int SCA_Is_Connected(SCA_Client_Instance_T* instance)
{
   int ret_val = 0;

   if (sca_Instance_Is_Valid(instance))
   {

      ret_val =
         ((instance->socket_ref >= 0) && (0 == instance->connect_result) && (SCA_DISCONNECTED != instance->connection_state));
   }

   return ret_val;
}

void SCA_Time_Add_Offset(struct timespec* time_spec, uint32_t time_offset_ms)
{
   time_t sec = (time_t) (time_offset_ms / 1000U);
   int32_t nsec = (int32_t) (time_offset_ms % 1000u) * 1000000;

   if ((time_spec->tv_nsec + nsec) >= 1000000000L)
   {
      nsec -= 1000000000;
      sec++;
   }
   time_spec->tv_sec += sec;
   time_spec->tv_nsec += nsec;
}

/*
 * Please refer to socket_client_api.h for the description.
 */
void SCA_Connect_With_Notification(SCA_Client_Instance_T* instance, char const * const tcp_ip_address, unsigned short port,
   SCA_Socket_Client_Unique_ID_T unique_id, SCA_Connection_Info_Callback_T connection_info_callback)
{
   pthread_attr_t thread_attr;
   struct sockaddr_in socket_adr_params;
   int err;

   SCA_DEBUG_0(">> SCA_Connect_With_Notification() - enter");
   if (!sca_Instance_Is_Valid(instance))
   {
      SCA_ERR_0("Invalid instance");
      /*****/
      return;
      /*****/
   }

   if (SCA_Is_Connected(instance))
   {
      SCA_ERR_0("Already connected");
      /*****/
      return;
      /*****/
   }

   /* Initialize instance */
   instance->connection_state = SCA_CONNECTING;
   SCA_DEBUG_0("connection_state = SCA_CONNECTING");

   memset(&socket_adr_params, 0, sizeof(socket_adr_params));
#ifdef OSX
   socket_adr_params.sin_len = sizeof(socket_adr_params);
#endif
   socket_adr_params.sin_family = AF_INET;
   socket_adr_params.sin_port = htons(port);
   socket_adr_params.sin_addr.s_addr = inet_addr(tcp_ip_address);
   memcpy(&instance->socket_adr, &socket_adr_params, sizeof(struct sockaddr_in));

   SCA_Set_UID(instance, unique_id);
   instance->socket_ref = -1;
   instance->connect_result = -1;
   instance->connection_info_callback = connection_info_callback;

   /* Create the thread in DETACHED state */
   err = pthread_attr_init(&thread_attr);
   if (err != 0)
   {
      SCA_ERR_2("pthread_attr_init() failed (%d): %s", err, strerror(err));
   }
   err = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
   if (err != 0)
   {
      SCA_ERR_2("pthread_attr_setdetachstate() failed (%d): %s", err, strerror(err));
   }
   err = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
   if (err != 0)
   {
      SCA_ERR_2("pthread_setcancelstate() failed (%d): %s", err, strerror(err));
   }

   /* Start connect_pthread() */
   err = pthread_create(&instance->thread_id, &thread_attr, &Client_Thread, instance);
   if (err != 0)
   {
      SCA_ERR_2("pthread_create() failed (%d): %s", err, strerror(err));
   }

   /* Release the memory for our attribute */
   err = pthread_attr_destroy(&thread_attr);
   if (err != 0)
   {
      SCA_ERR_2("pthread_attr_destroy() failed (%d): %s", err, strerror(err));
   }
   /*
    * Wait until Client_Thread has had 1 attempt to connect (or timeout) before
    * returning to caller.
    */
   {
      struct timespec timeout;
      (void) clock_gettime(CLOCK_REALTIME, &timeout);
      SCA_Time_Add_Offset(&timeout, SCA_INITIAL_CONNECT_TIMEOUT_MS);
      SCA_DEBUG_0("SCA_Connect_With_Notification: Waiting on Client_Thread");
      if (0 == sem_timedwait(&instance->start_stop_sem, &timeout))
      {
         SCA_DEBUG_0("SCA_Connect_With_Notification : Received signal from Client_Thread");
      }
      else
      {
         SCA_ERR_0("SCA_Connect_With_Notification() : Timed out waiting on Client_Thread");
      }
   }
   /* !! WARNING: Early returns in function body !! */
}

/*
 * Please refer to socket_client_api.h for the description.
 */
SCA_Client_Instance_T *SCA_Create_Instance_With_UID(SCA_Socket_Client_Unique_ID_T unique_id)
{
   SCA_Client_Instance_T *instance;

   instance = calloc(1, sizeof(*instance));

   if (instance != NULL)
   {
      pthread_mutexattr_t mutex_attr;
      int err;
      instance->valid_pattern = SCA_CONTEXT_PATTERN;
      /*
       * Initialize mutex used to lock the instance context
       */
      err = pthread_mutexattr_init(&mutex_attr);
      if (err != 0)
      {
         SCA_ERR_2("pthread_mutexattr_init() failed (%d): %s", err, strerror(err));
      }
      err = pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
      if (err != 0)
      {
         SCA_ERR_2("pthread_mutexattr_settype() failed (%d): %s", err, strerror(err));
      }
      err = pthread_mutex_init(&instance->instance_mutex, &mutex_attr);
      if (err != 0)
      {
         SCA_ERR_2("pthread_mutex_init() failed (%d): %s", err, strerror(err));
      }
      err = pthread_mutexattr_destroy(&mutex_attr);
      if (err != 0)
      {
         SCA_ERR_2("pthread_mutexattr_destroy() failed (%d): %s", err, strerror(err));
      }
      /*
       * Initialize mutex used for sending messages.
       */
      err = pthread_mutex_init(&instance->send_lock, NULL);
      if (err != 0)
      {
         SCA_ERR_2("pthread_mutex_init() failed (%d): %s", err, strerror(err));
      }
      /*
       * Initialize semaphore used for disconnect handshake.
       */
      err = sem_init(&instance->start_stop_sem, 0, 0);
      if (err != 0)
      {
         SCA_ERR_1("sem_init failed: %s", strerror(errno));
      }

      err = sem_init(&instance->connect_semaphore, 0, 0);
      if (err != 0)
      {
         SCA_ERR_1("sem_init failed: %s", strerror(errno));
      }

      if (unique_id != SCA_UNKNOWN_UID)
      {
         SCA_Set_UID(instance, unique_id);
      }
        //TODO
      //create_blocklist(&(instance->subscription_list), DEFAULT_ITEMS_PER_BLOCK, sizeof(SCA_Subscribe_Data_T), 0);
      /*
       * Allocate initial buffer used for receiving
       */
      instance->rd_buffer_size = SCA_INITIAL_MESSAGE_SIZE;
      instance->rd_buffer = malloc(SCA_INITIAL_MESSAGE_SIZE);
      if (NULL == instance->rd_buffer)
      {
         SCA_ERR_0("Failed to allocate initial read buffer");
         instance->rd_buffer_size = 0;
      }
   }

   return instance;
}

/*
 * Please refer to socket_client_api.h for the description.
 */
int SCA_Listen(SCA_Client_Instance_T* instance, SCA_Message_Callback_T callback)
{
   return SCA_Listen_With_Context(instance, (SCA_Message_Context_Callback_T) callback, NULL);
}

/*
 * Please refer to socket_client_api.h for the description.
 */
int SCA_Listen_With_Context(SCA_Client_Instance_T* instance, SCA_Message_Context_Callback_T callback, void* context)
{

   int result = -1;

   if (sca_Instance_Is_Valid(instance))
   {
      instance->context = context;
      instance->callback = callback;
      result = 0;
   }
   else
   {
      SCA_ERR_0("SCA_Listen_With_Context: Cannot handle NULL instance");
   }

   return result;
}

/*
 * Please refer to socket_client_api.h for the description.
 */
int SCA_Send(SCA_Client_Instance_T* instance, SCA_Socket_Client_Unique_ID_T destination_client_uid, uint32_t code, uint32_t data,
   void const * const payload, uint32_t payload_size)
{
   /* TODO: copy-and-short-circuit for local client destination
    (but what about Spying on these messages?) */
   int ret_val = -1;

   if (sca_Instance_Is_Valid(instance))
   {
      ret_val = sca_Send_Message(instance, destination_client_uid, code, data, payload, payload_size);
   }

   return ret_val;
}

static void Shutdown(SCA_Client_Instance_T* instance)
{
   if (sca_Instance_Is_Valid(instance))
   {
      //sca_Shutdown_SSL(instance);

      instance->connect_result = -1;

      /* Close the socket */
      if (shutdown(instance->socket_ref, SHUT_RDWR) != 0)
      {
         SCA_ERR_1("shutdown(m_accept_fd) FAILED: %s", strerror(errno));
      }
      if (close(instance->socket_ref) != 0)
      {
         SCA_ERR_1("close(m_accept_fd) FAILED: %s", strerror(errno));
      }
      instance->socket_ref = -1;
   }
}

/**
 * This is called when SIGPIPE is received
 *
 * Normally this means SocketServer unexpectedly died, but it could be something more mundane
 * like a cable got disconnected
 */
static void SIGPIPE_Handler(int signo)
{
   //Tr_Fault("SIGPIPE occurred");
}

/**
 * Waits until data is available to be read from the socket or until it is
 * determined that the connection has been severed.
 */
static void Wait_For_Receive_Data(SCA_Client_Instance_T* instance)
{
   int num_timeouts = 0;
   int poll_result = 0;

   while ((0 == poll_result) && SCA_Is_Connected(instance))
   {
      struct pollfd fds =
         { 0 };
      fds.fd = instance->socket_ref;
      fds.events = POLLIN;

      /* Wait for data to read or a timeout */
      poll_result = poll(&fds, 1, SCA_POLL_TIMEOUT_MS);
      if (poll_result > 0)
      {
         /* No error and no timeout; so, data is available to be read. */
      }
      else if (poll_result < 0 && errno != EINTR)
      {
         /* An unexpected error occurred - disconnect */
         SCA_ERR_1("poll() failed: %s", strerror(errno));
         Notify_Client_Of_Connection_Info(instance, SCA_DISCONNECTED, SCA_DISCONNECT_UNCLEAN);
         sca_Disconnect_On_Err(instance);
      }
      else if (poll_result < 0 && errno == EINTR)
      {
         /*A signal may have caused this so ignore and retry*/
         poll_result=0;
      }
      else
      {
         /* Timed out. Send query to server and try again until re-tries over. */
         ++num_timeouts;
         if (num_timeouts <= SCA_MAX_NUM_POLL_TIMEOUTS)
         {
            //Tr_Info_Hi_1("%s: Asking server to validate connection", instance->uid_str);
            sca_Send_Message(instance, SS_CONTROL_DESTINATION, SS_SOH, SS_SOH_CLIENT_CHECK, NULL, 0);
         }
         else
         {
            SCA_ERR_0("Failed to hear from server in allotted time. Terminating connection.");
            Notify_Client_Of_Connection_Info(instance, SCA_DISCONNECTED, SCA_DISCONNECT_UNCLEAN);
            sca_Disconnect_On_Err(instance);
         }
      }
   }
}

static int Write_Message(SCA_Client_Instance_T* instance, SS_Message_Header_T const * wr_hdr, void const * const payload,
   size_t payload_size)
{
   int result = -1;
   size_t num_written = 0;
   size_t bytes_remaining = sizeof(*wr_hdr) + payload_size;

   while (bytes_remaining > 0)
   {
      struct iovec msg_iovec[2];
      int iovec_cnt = 0;
      ssize_t num_sent;

      if (num_written < sizeof(*wr_hdr))
      {
         msg_iovec[iovec_cnt].iov_base = (char *) wr_hdr + num_written;
         msg_iovec[iovec_cnt].iov_len = sizeof(*wr_hdr) - num_written;
         iovec_cnt++;
         if (payload_size > 0)
         {
            msg_iovec[iovec_cnt].iov_base = (char*) payload;
            msg_iovec[iovec_cnt].iov_len = payload_size;
            iovec_cnt++;
         }
      }
      else
      {
         msg_iovec[iovec_cnt].iov_base = (char*) payload + (num_written - sizeof(*wr_hdr));
         msg_iovec[iovec_cnt].iov_len = payload_size - (num_written - sizeof(*wr_hdr));
         iovec_cnt++;
      }

      /* Attempt to write remainder to socket */
      SCA_DEBUG_1("Attempting to write %d  bytes", (int )bytes_remaining);
      num_sent = writev(instance->socket_ref, msg_iovec, iovec_cnt);

      if (num_sent <= 0)
      {
         if (EINTR == errno)
         {
            /* just try again if interrupted by a signal */
            SCA_DEBUG_0("writev() call returned due to EINTR - retrying");
            Notify_Client_Of_Connection_Info(instance, SCA_DISCONNECTED, SCA_WRITEV_EINTR_ERROR);
         }
         else
         {
            /* For any other errors, close connection */
            SCA_ERR_1("writev() FAILED: %s", strerror(errno));
            Notify_Client_Of_Connection_Info(instance, SCA_DISCONNECTED, SCA_UNKNOWN_WRITEV_ERROR);
            sca_Disconnect_On_Err(instance);
            break;
         }
      }
      else
      {
         bytes_remaining = bytes_remaining - num_sent;
         num_written += num_sent;
      }

   } /* while(bytes_remaining > 0) */

   if (0 == bytes_remaining)
   {
      result = 0;
   }

   SCA_DEBUG_1("Exiting having written %d bytes.", (int )(sizeof(*wr_hdr) + payload_size - bytes_remaining));
   return result;
}