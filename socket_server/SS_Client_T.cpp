/*===========================================================================*/
/**
 * @file SS_Client_T.cpp
 *
 * Implementation of the SocketServer logic for individual clients.
 *
 * %full_filespec: SS_Client_T.cpp~3:c++:ctc_ec#1 %
 * @version %version: 3 %
 * @author  %derived_by: zjz2j2 %
 * @date    %date_modified: Fri Jul  6 09:50:50 2018 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2013-2014 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * @section ABBR ABBREVIATIONS:
 *   - SOH = State Of Health
 *   - SS  = Socket Server
 *   - UID = Unique IDentifier
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *
 *   - Requirements Document(s):
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *     - BASA Naming Conventions, version 2.0
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *    - None
 *
 * @ingroup Socket_Server_T
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include "Socket_Server_T.hpp"
#include "SS_Client_T.hpp"
//#include "SS_Logging.hpp"
//#include "SYHLP_Clock_T.hpp"
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/** Identify module for dbg_trace. */
#define EM_F_ID EM_FILE_ID(SOCKET_SERVER_MODULE_ID, 3)

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Const Object Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Object Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/


/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * NOTE: For descriptions of class members, please refer to the comments in
 *       SS_Client_T.hpp.
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

SS_Client_T::SS_Client_T(Socket_Server_T& server, int socket_fd) :
   m_last_rcvd_msg_time(),
   m_msgs_recv(0),
   m_msgs_sent(0),
   m_outgoing_msg(NULL),
   m_outgoing_queue(),
   m_published_msg_codes(),
   m_recv_header_read(0),
   m_recv_header(),
   m_recv_payload_read(0),
   m_recv_payload(NULL),
   m_recv_total(0),
   m_send_header(),
   m_send_total(0),
   m_server(server),
   m_socket_fd(socket_fd),
   m_spied_from(),
   m_spied_to(),
   m_spy_from(),
   m_spy_to(),
   m_subscribed_msg_codes(),
   m_transmit_header_written(0),
   m_transmit_payload_size(0),
   m_transmit_payload_written(0),
   m_uid(0),
   m_client_description()
{
   /* Initialize the handler for each SPY message */
   #undef SS_SPY_MESSAGE
   #define SS_SPY_MESSAGE(msg) m_spy_handlers[msg] = &SS_Client_T::_##msg##_Processor;

   SS_SPY_MESSAGES

   SS_DBG(__FUNCTION__);
}

SS_Client_T::~SS_Client_T()
{
   SS_DBG(__FUNCTION__ << " (" << this << ") " << *this);

   Stop_Spying();

   Shutdown();

   free(m_recv_payload);

   while (!m_published_msg_codes.empty())
   {
      std::set<uint32_t>::iterator msg_code_it = m_published_msg_codes.begin();

      SS_DBG("Client had published message " << SS_Hex_Data_T(*msg_code_it));

      m_published_msg_codes.erase(msg_code_it);
   }

   m_server.Clean_Up_Client(m_uid);

   while (!m_subscribed_msg_codes.empty())
   {
      std::set<uint32_t>::iterator msg_code_it = m_subscribed_msg_codes.begin();
      Unsubscribe(*msg_code_it);
   }
   delete m_outgoing_msg;
   while (!m_outgoing_queue.empty())
   {
      delete m_outgoing_queue.front();
      m_outgoing_queue.pop();
   }
}

std::string SS_Client_T::Msg_Hdr_To_String(void)
{
   std::ostringstream oss;
   SS_UID_T destination(m_recv_header.destination);

   oss.flags(std::ostream::hex | std::ostream::showbase| std::ostream::uppercase);
   oss << "destination: " << destination << "; code: " << m_recv_header.code <<
          "; data: " << m_recv_header.data << "; sz: " << m_recv_header.payload_size;

   return oss.str();
}

void SS_Client_T::Prepare_Outgoing_Message(SS_Message_T const *message)
{
   m_outgoing_msg = message;
   m_transmit_payload_size = message->Get_Payload_Size();
   m_transmit_header_written = 0;  // None of the header has been sent yet
   m_transmit_payload_written = 0; // None of payload (if there is one) has been sent yet
   // Data is sent in network order so must be converted from internal representation
   m_send_header.destination = ntohl(message->Get_Destination().Get_Value());
   m_send_header.code = ntohl(message->Get_Code().Get_Value());
   m_send_header.data = ntohl(message->Get_Data().Get_Value());
   m_send_header.payload_size = ntohl(message->Get_Payload_Size());
}

void SS_Client_T::Process_Non_Broadcast_Message(SS_Message_T* rcvd_msg)
{
   SS_DBG(__FUNCTION__ << " - " << *rcvd_msg);

   m_server.Get_Logger().Log(rcvd_msg, SS_JSON_Message_Log_T::RECEIVE, true);

   if (SS_CONTROL_DESTINATION == rcvd_msg->Get_Destination().Get_Value())
   {
      Process_Control_Message(rcvd_msg);
   }
   else if (!rcvd_msg->Send(m_server))
   {
      // If the message wasn't sent, then it must be deleted to prevent a leak
      delete rcvd_msg;
   }
   else
   {
      // rcvd_msg will be deleted after it has been sent
   }
}

ssize_t SS_Client_T::Read_From_Socket(char *buffer, size_t num_bytes_to_read)
{
   Tr_Cpp_Info_Lo("Entering " << __FUNCTION__ << " for " << m_uid);

   /* May receive partial messages, this keeps track of where we have "filled to buffer to" so far */
   char* read_location = buffer;

   /* May receive partial messages, this keeps track of how many bytes remain to be read */
   size_t bytes_remaining = num_bytes_to_read;

   /* While more bytes to read... */
   while(bytes_remaining > 0)
   {
      /* Read a buffer-full of data from the socket */
      Tr_Cpp_Info_Lo("Attempting to read " << bytes_remaining << " bytes from " << m_uid);
      ssize_t num_rcvd = recv(m_socket_fd, read_location, bytes_remaining, MSG_DONTWAIT);

      /* If num_rcvd < 0, then an error occured... */
      if(0 == num_rcvd)
      {
         // peer has shutdown
         if (!m_server.m_exit_requested)
         {
            Tr_Cpp_Fault("recv() returned 0 (peer shutdown) for " << "(" << this << ") " << m_uid);
         }
         Shutdown();
         break;
      }
      else if(num_rcvd < 0)
      {
         if ((EWOULDBLOCK == errno) || (EAGAIN == errno))
         {
            // can't read w/o blocking - so stop with what has been read so far
            SS_DBG("Exiting because no more data is available without blocking");
            break; // exit while loop
         }
         else if (EINTR == errno)
         {
            // just try again if interrupted by a signal
            SS_DBG("recv() call returned due to EINTR - retrying");
         }
         else
         {
            // For any other errors, close connection
            Tr_Cpp_Fault("recv() FAILED for " << "(" << this << ") " << m_uid << ": " << strerror(errno));
            Shutdown();
            break;
         }
      }
      else
      {
         m_recv_total += num_rcvd;
         bytes_remaining = bytes_remaining - num_rcvd;
         read_location = read_location + num_rcvd;
      }
   }

   Tr_Cpp_Info_Lo("Exiting " << __FUNCTION__ << " having read " <<
                    (num_bytes_to_read - bytes_remaining) << " bytes from " << m_uid);
   return (num_bytes_to_read - bytes_remaining);
}

void SS_Client_T::Receive(void)
{
   Tr_Cpp_Info_Lo("Entering " << __FUNCTION__ << " for " << m_uid);

   // Finish reading the header, if not already read
   if (m_recv_header_read < sizeof(m_recv_header))
   {
      ssize_t num_read =
         Read_From_Socket((char*)&m_recv_header + m_recv_header_read,
                          sizeof(m_recv_header) - m_recv_header_read);
      if (Is_Connected())
      {
         m_recv_header_read += num_read;
         if (sizeof(m_recv_header) == m_recv_header_read)
         {
            // Data is sent in network order so must be converted to internal representation
            m_recv_header.destination = ntohl(m_recv_header.destination);
            m_recv_header.code = ntohl(m_recv_header.code);
            m_recv_header.data = ntohl(m_recv_header.data);
            m_recv_header.payload_size = ntohl(m_recv_header.payload_size);
            /*Tr_Cpp_Info_Lo(Msg_Hdr_To_String() << " from " << m_uid);*/
            m_recv_payload_read = 0; // None of payload (if there is one) has been read yet
            if (m_recv_header.payload_size > 0)
            {
               m_recv_payload = (char *)malloc(m_recv_header.payload_size);

               if (NULL == m_recv_payload)
               {
                  Tr_Cpp_Fault("FAILED to allocate memory for message payload from " <<
                         m_uid << " of size " << m_recv_header.payload_size);
                  Shutdown();
               }
            }
         }
      }
   }
   // Once header is read, read any payload to finish up message
   if (Is_Connected() && (sizeof(m_recv_header) == m_recv_header_read))
   {
      if (m_recv_payload_read < m_recv_header.payload_size)
      {
         ssize_t num_read =
            Read_From_Socket(m_recv_payload + m_recv_payload_read,
                             m_recv_header.payload_size - m_recv_payload_read);
         if (Is_Connected())
         {
            m_recv_payload_read += num_read;
         }
      }
      if (Is_Connected() && (m_recv_payload_read == m_recv_header.payload_size))
      {
         m_msgs_recv++;

         Update_Time_Of_Last_Message();

         if (SS_BROADCAST_DESTINATION == m_recv_header.destination)
         {
            /*
             * Broadcast messages "persist" in the server's broadcast map so that a
             * subsequent subscriber gets the most recent broadcast. Payload will only be
             * deleted when a new payload is received.
             */
            m_published_msg_codes.insert(m_recv_header.code);
            m_server.Broadcast_Message(Get_UID(), m_recv_header, m_recv_payload);
         }
         else
         {
            /*
             * Non-broadcast messages are dynamic - they only "live" until they have
             * been sent.
             */
            SS_Message_T *rcvd_msg = new SS_Message_T(m_recv_header.destination,
                                                      m_recv_header.code,
                                                      m_recv_header.data,
                                                      m_recv_header.payload_size,
                                                      m_recv_payload,
                                                      m_uid);

            Process_Non_Broadcast_Message(rcvd_msg);
         }
         /*
          * The message data has been moved to the message object; so, prepare
          * this client for receiving its next message.
          */
         m_recv_header_read = m_recv_payload_read = 0;
         m_recv_payload = NULL;
      }
   }
}

void SS_Client_T::Stop_Spying(void)
{
   SS_DBG(__FUNCTION__ << " (" << this << ") " << *this);
   //
   // Remove all existing "TO"/"FROM" spying by this client
   //
   std::set<uint32_t>::iterator uid_iterator = m_spy_to.begin();
   while (uid_iterator != m_spy_to.end())
   {
      Remove_To_Spy(this, *uid_iterator);
      uid_iterator = m_spy_to.begin();
   }

   uid_iterator = m_spy_from.begin();
   while (uid_iterator != m_spy_from.end())
   {
      Remove_From_Spy(this, *uid_iterator);
      uid_iterator = m_spy_from.begin();
   }
}

void SS_Client_T::Shutdown(void)
{
   Tr_Cpp_Info_Lo("Entering " << __FUNCTION__);
   if (m_socket_fd != -1)
   {
      Tr_Cpp_Info_Lo("shutdown/close of m_socket_fd " << m_socket_fd);
      if (shutdown(m_socket_fd, SHUT_RDWR) != 0)
      {
         Tr_Cpp_Fault("shutdown(" << m_socket_fd << ") FAILED for " << m_uid << ": " << strerror(errno));
      }
      if (close(m_socket_fd) != 0)
      {
         Tr_Cpp_Fault("close(" << m_socket_fd << ") FAILED for " << m_uid << ": " << strerror(errno));
      }
      m_socket_fd = -1;
   }
}

void SS_Client_T::Subscribe(SS_Hex_Data_T msg_code, bool_t enable_report)
{
   Tr_Cpp_Info_Lo(m_uid << " is subscribing to message code " << msg_code);
   m_subscribed_msg_codes.insert(msg_code.Get_Value());
   Tr_Cpp_Info_Lo(m_uid << " is subscribed to " << m_subscribed_msg_codes.size() << " message codes.");
   m_server.subscribe(this, msg_code, enable_report);
}

void SS_Client_T::Transmit(void)
{
   size_t header_bytes_remaining = sizeof(m_send_header) - m_transmit_header_written;
   size_t msg_bytes_remaining = header_bytes_remaining +
                                (m_transmit_payload_size - m_transmit_payload_written);

   SS_DBG("Entering " << __FUNCTION__ << " for " << m_uid << " with " << msg_bytes_remaining << " bytes to write.");

   while (msg_bytes_remaining > 0)
   {
      struct iovec msg_iovec[2]; // at most 2 parts: 1) header, 2) payload
      int iovec_cnt = 0; // # of parts to write

      // Stage any header that has not been written
      if (header_bytes_remaining > 0)
      {
         if (0 == m_transmit_header_written)
         {
            SS_DBG("Initiating message (code = " << m_outgoing_msg->Get_Code() <<
               ") for " << m_uid << " from " << m_outgoing_msg->Get_Source());
         }
         if (m_transmit_header_written < sizeof(m_send_header))
         {
            msg_iovec[iovec_cnt].iov_base = (char *) &m_send_header + m_transmit_header_written;
            msg_iovec[iovec_cnt].iov_len = header_bytes_remaining;
            iovec_cnt++;
         }
      }
      // Stage any payload that has not been written
      if (m_transmit_payload_written < m_transmit_payload_size)
      {
         msg_iovec[iovec_cnt].iov_base = (char*) m_outgoing_msg->Get_Payload() + m_transmit_payload_written;
         msg_iovec[iovec_cnt].iov_len = m_transmit_payload_size - m_transmit_payload_written;
         iovec_cnt++;
      }

      /* Attempt to write everything to the socket */
      SS_DBG("Attempting to write " << msg_bytes_remaining << " bytes.");
      ssize_t writev_result = writev(m_socket_fd, msg_iovec, iovec_cnt);

      if (writev_result >= 0) // No error
      {
         size_t num_sent =  writev_result;
         SS_DBG(num_sent << " bytes were written.");
         if (header_bytes_remaining > 0) // Some of the write was header bytes
         {
            if (num_sent > header_bytes_remaining) // Some of the write was also for the payload
            {
               num_sent -= header_bytes_remaining; // calc. amount of payload written
               m_transmit_header_written = sizeof(m_send_header); // header write is done
            }
            else // everything written was for the header
            {
               m_transmit_header_written += num_sent;
               num_sent = 0; // nothing was written for the payload
            }
         }
         m_transmit_payload_written += num_sent;
         // recalculate bytes_remaining to see if another writev call is needed
         header_bytes_remaining = sizeof(m_send_header) - m_transmit_header_written;
         msg_bytes_remaining = header_bytes_remaining +
                               (m_transmit_payload_size - m_transmit_payload_written);

         if (0 == msg_bytes_remaining) // message has been sent w/o error
         {
            m_server.Get_Logger().Log(m_outgoing_msg, SS_JSON_Message_Log_T::TRANSMIT);
            m_msgs_sent++;
            m_send_total += m_outgoing_msg->m_payload_size + sizeof(m_send_header);
         }
      }
      else // an error was reported
      {
         if ((EWOULDBLOCK == errno) || (EAGAIN == errno))
         {
            // can't write w/o blocking - so stop with what has been written so far
            SS_DBG("Exiting because no more data could be written without blocking");
            break; // .. out of while
         }
         if (EINTR == errno)
         {
            /* just try again if interrupted by a signal */
            SS_DBG("writev() call returned due to EINTR - retrying");
         }
         else
         {
            /* For any other errors, close connection */
            Tr_Cpp_Fault("writev() FAILED: " << strerror(errno));
            Shutdown();
            msg_bytes_remaining = 0; // abort this message
         }
      }

   } // while (msg_bytes_remaining > 0)

   if (0 == msg_bytes_remaining) // Done with message
   {
      //
      // This is where the dynamically allocated message is freed; this can only be
      // done after it is completely sent (or an unrecoverable error occurs)
      //
      delete m_outgoing_msg;

      if (m_outgoing_queue.empty())
      {
         Tr_Cpp_Info_Lo("Message queue empty for " << m_uid);
         m_outgoing_msg = NULL; // no more transmission in progress for this client
      }
      else
      {
         m_outgoing_msg = m_outgoing_queue.front();
         m_outgoing_queue.pop();
         Tr_Cpp_Info_Lo("De-queuing message (code = " << m_outgoing_msg->Get_Code() <<
                ") for " << m_uid << " from " << m_outgoing_msg->Get_Source());
         Prepare_Outgoing_Message(m_outgoing_msg);
         // Don't actually start the next message in order to help prevent this
         // client from not yielding to other clients
      }
   }

   SS_DBG("Exiting " << __FUNCTION__ << " for " << m_uid << " with " << msg_bytes_remaining << " bytes remaining.");
}

void SS_Client_T::Transmit(SS_Message_T const *message, bool_t copy_it)
{
   SS_Message_T const *msg_to_use;

   SS_Log_Sent_Message(this, message);

   if (copy_it)
   {
      /* Make a full copy of this message for this client, setting the destination to
       * this client's uid. This ensures that the information contained in the
       * new message is correct for the directed send to this client.
       */
      msg_to_use = new SS_Message_T(m_uid,
                                    message->Get_Code().Get_Value(),
                                    message->Get_Data().Get_Value(),
                                    message->Get_Payload_Size(),
                                    (char*)message->Get_Payload(),
                                    message->Get_Source(),
                                    true,
                                    message->Get_Message_UID());
   }
   else
   {
      // Just use the message w/o copying it. The client becomes the exclusive
      // "owner" of the message and will delete (free) it when it has been sent
      msg_to_use = message;
   }

   if (NULL == m_outgoing_msg) // Not currently sending to this client
   {
      Tr_Cpp_Info_Lo("Sending message now");
      Prepare_Outgoing_Message(msg_to_use);
      Transmit(); // Attempt to send some data now
   }
   else // Another message is being sent, queue this one up
   {
      Tr_Cpp_Info_Lo("Queuing message");
      m_outgoing_queue.push(msg_to_use);
   }
}

void SS_Client_T::Update_Time_Of_Last_Message(void)
{
   m_last_rcvd_msg_time = SYHLP_Clock_mS();
}

void SS_Client_T::Unsubscribe(SS_Hex_Data_T msg_code)
{
   Tr_Cpp_Info_Lo(m_uid << " is unsubscribing from message code " << msg_code);
   m_subscribed_msg_codes.erase(msg_code.Get_Value());
   Tr_Cpp_Info_Lo(m_uid << " is subscribed to " << m_subscribed_msg_codes.size() << " message codes.");
   m_server.unsubscribe(this, msg_code);
}

std::ostream& operator<<(std::ostream& out, SS_Client_T const& client)
{
   out << " - socket_fd: " << client.m_socket_fd << "; UID: " << client.m_uid;
   return out;
}

/*===========================================================================*/
/*!
 * @file SS_Client_T.cpp
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 12-Nov-2013 Kirk Bailey REV 4
 *   - Fixed Klocwork issues.
 *
 * - 19-Nov-2013 Kirk Bailey REV 5, 6
 *   - Added support for multiple to/from spy clients.
 *
 * - 23-Nov-2013 Kirk Bailey Rev. 7
 *   - Resolved Klocwork issues.
 *
 * - 08-Dec-2013 Kirk Bailey REV 8
 *   - Added Stop_Spying() method.
 *
 * - 09-Jan-2014 Kirk Bailey REV 9
 *   - Made sure that if an unrecoverable error occurs during the transmission
 *     of a message that it is freed.
 *
 * - 12-Jan-2015 Joel Kiger Rev 10
 *  - Task kok_inf#18016 Change SOH timer to Sync Helper Clock so monotonic can be used
 */
/*===========================================================================*/
/** @} doxygen end group */

