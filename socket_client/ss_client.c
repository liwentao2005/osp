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
#include "socket_client_api.h"
#include "ss_version.h"

int func_cnt = 0;
int now_flag = 0;

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

      create_blocklist(&(instance->subscription_list), DEFAULT_ITEMS_PER_BLOCK, sizeof(SCA_Subscribe_Data_T), 0);
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
int SCA_Listen(SCA_Client_Instance_T *instance, SCA_Message_Callback_T callback)
{
    printf("%s--%d.\n", __FILE__, __LINE__);
    return 0;
}
