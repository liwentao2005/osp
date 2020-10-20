#ifndef SS_CLIENT_T_HPP
#   define SS_CLIENT_T_HPP
/*===========================================================================*/
/**
 * @file SS_Client_T.hpp
 *
 *   Declares the SS_Client_T class. An object of this type is created for
 *   each client that connects to a server.
 *
 * %full_filespec:SS_Client_T.hpp~2:ascii:ctc_ec#4 %
 * @version %version:2 %
 * @author  %derived_by:bz08fr %
 * @date    %date_modified:Fri Jun  3 09:15:22 2016 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2013 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
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
 *
 * @ingroup Socket_Server_T
 * @{
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/

#   include <iostream>
#   include <json-c/json.h>
#   include <queue>
#   include <set>
#   include <string>

class Socket_Server_T; // client and server reference one another
class SS_Client_T
{
      friend class Socket_Server_T; // Allow Socket_Server_T to access internal members
   public:

      /**
       * Constructs a SS_Client_T object that is connected to the specified
       * server and communicates on the specified file descriptor.
       *
       * @param server  The server to which the client is connected.
       * @param socket_fd  The file descriptor used to communicate to it.
       */
      SS_Client_T(Socket_Server_T& server, int socket_fd);
      /**
       * Destroys an object. This is virtual to allow for inheritance.
       */
      virtual ~SS_Client_T();
      /**
       * @return The file descriptor used to communicate with this client.
       */
      int Get_Socket_FD(void) const { return m_socket_fd; }

   protected:
      /** The time of the last valid message received from the client. */
      uint32_t m_last_rcvd_msg_time;

      /** Number of messages received by the client. */
      uint32_t m_msgs_recv;

      /** Number of messages sent by the client. */
      uint32_t m_msgs_sent;


      /** Number of bytes sent by the client. */
      size_t m_send_total;

      /* Reference to the associated SocketServer instance */
      Socket_Server_T& m_server;

      /** The server to which the client is connected. */
      int m_socket_fd;

      /** Set of UIDs that are spying on messages FROM this client. */
      std::set<uint32_t> m_spied_from;

      /** Set of UIDs that are spying on messages TO this client. */
      std::set<uint32_t> m_spied_to;

      /** Set of UIDs that this client is spying on messages FROM. */
      std::set<uint32_t> m_spy_from;

      /** Set of UIDs that this client is spying on messages TO. */
      std::set<uint32_t> m_spy_to;

      /** std::set of message codes to which this client is subscribed. */
      std::set<uint32_t> m_subscribed_msg_codes;

      /** Number of bytes written for the most recent transmit message header. */
      size_t m_transmit_header_written;

      /** Size of the most recently transmitted message payload. */
      size_t m_transmit_payload_size;

      /** Number of bytes of the most recent transmitted message payload sent. */
      size_t m_transmit_payload_written;

      /** This is the description reported by the client. */
      std::string m_client_description;

   private:

      /** Do not allow copying */
      SS_Client_T(SS_Client_T const &rhs);

      /** Do not allow assignment */
      SS_Client_T& operator=(SS_Client_T const &rhs);
};

/*===========================================================================*/
/*!
 * @file SS_Client_T.hpp
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 10-Jan-2013 Kirk Bailey
 *   - Created initial file comments.
 *
 * - 11-Oct-2013 Kirk Bailey REV 3
 *   - Fixed Klocwork issues.
 *
 * - 21-Oct-2013 Kirk Bailey REV 4
 *   - Fixed Doxygen comments.
 *
 * - 19-Nov-2013 Kirk Bailey REV 5
 *   - Added support for multiple to/from spy clients.
 *
 * - 08-Dec-2013 Kirk Bailey REV 6
 *   - Added Stop_Spying() method.
 *
 * - 17-Sep-2014 Joel Kiger Rev 7
 *  - Task kok_inf#12200 Fix SSL, add SSL configuration and add better error messages
 *
 * - 17-Sep-2014 Joel Kiger Rev 8
 *  - Task kok_inf#12290 Remove blocking for ssl_accept and fix valgrind errors
 *
 * - 20-Sep-2014 Joel Kiger Rev 9
 *  - Task kok_inf#12430 Stop SSL from trying to send if handshake is not complete
 *
 * - 12-Jan-2015 Joel Kiger Rev 10
 *  - Task kok_inf#18016 Change SOH timer to Sync Helper Clock so monotonic can be used
 */
/*===========================================================================*/
/** @} doxygen end group */
#endif // SS_CLIENT_T_HPP
