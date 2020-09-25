#ifndef SS_INTERFACE_H
#   define SS_INTERFACE_H
/*===========================================================================*/
/**
 * @file ss_interface.h
 *
 *   Global declarations for SocketServer.
 *
 * %full_filespec: ss_interface.h~1:incl:ctc_ec#4 %
 * @version %version: 1 %
 * @author  %derived_by: bz08fr %
 * @date    %date_modified: Mon Feb 29 13:54:02 2016 %
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
 * @ingroup Socket_Server_T Socket server
 * @{
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/

#   include "reuse.h"
//#   include "socket_server_acfg.h"



/** UID for broadcasting a message. */
#   define SS_BROADCAST_DESTINATION (0xFFFFFFFF)

/** UID To indicate that this message does not have a valid source */
#   define SS_SOURCE_INVALID (0xFFFFFFFF)

/** UID for sending a control message to the server. */
#   define SS_CONTROL_DESTINATION (0x00000000)

/** Message code reserved for signifying "all messages". */
#   define SS_MESSAGE_CODE_ALL (0xFFFFFFFF)

/** Domain reserved for signifying "all domains". */
#   define SS_DOMAIN_ALL (0xFFFF)

/**
 * Data sent in an SOH message for a handshake initiated by the client; i.e.,
 * when the client wants to see if the server is still connected. The server
 * sends the same value in response.
 */
#   define SS_SOH_CLIENT_CHECK 1

/**
 * Data sent in an SOH message for a handshake initiated by the server; i.e.,
 * when the server wants to see if the client is still connected. The client
 * sends the same value in response.
 */
#   define SS_SOH_SERVER_CHECK 0

/**
 * Every SS message starts with the following 16-byte header.
 */
typedef struct
{
   uint32_t destination;  /* UID of destination                   */
   uint32_t code;         /* Message code that ids the message    */
   uint32_t data;         /* 32-bit data that is message-specific */
   uint32_t payload_size; /* # of bytes that follow this header as message-specific payload. */
   /* char  payload[1];    NOTE: don't want any padding in this struct */
}
SS_Message_Header_T;

/**
 * Converts 4 characters into a 32-bit UID.
 */
#   ifndef SS_FOURCC_TO_UID
#      define SS_FOURCC_TO_UID(a,b,c,d)\
   (uint32_t) (((uint32_t)(a) << 24) + ((uint32_t)(b) << 16) +((uint32_t)(c) <<  8) + (uint32_t)(d))
#   endif

#   define SS_Get_Msg_Code_Domain(code) ((code >> 16) & 0xFFFF)

/**
 * The following structure defines the payload sent by the server in reply to a
 * SS_DUMP_CLIENT_STATS SPY request. One such message is generated per client
 * and when all client data has been sent, the series of messages is followed
 * by a SS_CLIENT_STATS_DONE message.
 */
typedef struct
{
      char  *log_buf;       /** DEPRECATED - For internal server use only. */
      size_t log_buf_sz;    /** DEPRECATED - For internal server use only. */

      uint32_t client_ref;  /** The socket file descriptor in use by the client. */
      uint32_t uid;         /** The UID of this client */

      uint32_t num_recvs;   /** Total # of recv calls made by client. */
      uint32_t num_sends;   /** Total # of send calls made by client. */
      uint32_t recv_total;  /** total # of bytes received by client.  */
      uint32_t send_total;  /** total # of bytes received by client.  */
}
SS_Per_Client_Data_T;

/**
 * X MACRO that declares the server's control messages.
 */
#define SS_CONTROL_MESSAGES                  \
   SS_CONTROL_MESSAGE(SS_SOH)                \
   SS_CONTROL_MESSAGE(SS_HELLO)              \
   SS_CONTROL_MESSAGE(SS_GOODBYE)            \
   SS_CONTROL_MESSAGE(SS_SUBSCRIBE)          \
   SS_CONTROL_MESSAGE(SS_UNSUBSCRIBE)        \
   SS_CONTROL_MESSAGE(SS_SPY)                \
   SS_CONTROL_MESSAGE(SS_PERSISTENCY)        \
   SS_CONTROL_MESSAGE(SS_SUBSCRIBE_NO_REPORT)\

/**
 * X MACRO that declares the server's control message responses.
 */
#define SS_CONTROL_MESSAGE_RESPONSES         \
   SS_CONTROL_MESSAGE(SS_SPY_RESPONSE)       \
   SS_CONTROL_MESSAGE(SS_CLIENT_CONNECTED)   \
   SS_CONTROL_MESSAGE(SS_CLIENT_DISCONNECTED)\
   SS_CONTROL_MESSAGE(SS_CLIENT_REFUSED)     \

#undef  SS_CONTROL_MESSAGE
#define SS_CONTROL_MESSAGE(msg) msg,
/**
 * Create enum tags with the control message names.
 */
typedef enum
{
   SS_CONTROL_MESSAGES
   SS_NUM_CONTROL_MESSAGES,
   SS_RESPONSE_START = ((SS_NUM_CONTROL_MESSAGES/32 + 1)*32)-1, /* avoid renumbering response codes every time a control code is added */
   SS_CONTROL_MESSAGE_RESPONSES
}
SS_Control_Message_Code_T;

/**
 * X MACRO that declare's the server's SPY control messages.
 */
#define SS_SPY_MESSAGES\
   SS_SPY_MESSAGE(SS_GET_CLIENT_SOCKET_REF_LIST)\
   \
   SS_SPY_MESSAGE(SS_GET_CLIENT_UNIQUE_ID_LIST)\
   \
   SS_SPY_MESSAGE(SS_GET_MESSAGES_CLIENT_SUBSCRIBES_TO)\
   \
   SS_SPY_MESSAGE(SS_CLEAR_PUBLISHED_MESSAGE_DATA)\
   SS_SPY_MESSAGE(SS_GET_PUBLISHED_MESSAGE_DATA)\
   SS_SPY_MESSAGE(SS_PUBLISHED_MESSAGE_DATA_DONE)\
   SS_SPY_MESSAGE(SS_PUBLISHED_MESSAGE_DATA_RECORD)\
   \
   SS_SPY_MESSAGE(SS_CANCEL_SPY_ON_MESSAGES)\
   SS_SPY_MESSAGE(SS_SPY_ON_MESSAGES_FROM_CLIENT)\
   SS_SPY_MESSAGE(SS_SPY_ON_MESSAGES_TO_CLIENT)\
   \
   SS_SPY_MESSAGE(SS_CANCEL_SPY_ON_MESSAGES_WITH_CODE)\
   SS_SPY_MESSAGE(SS_CLIENTS_RECEIVING_MESSAGE_REPORT)\
   SS_SPY_MESSAGE(SS_MESSAGES_RECEIVED_REPORT)\
   SS_SPY_MESSAGE(SS_SPY_ON_MESSAGES_WITH_CODE)\
   \
   SS_SPY_MESSAGE(SS_CANCEL_SPY_ON_DOMAIN)\
   SS_SPY_MESSAGE(SS_CLIENTS_RECEIVING_DOMAIN_REPORT)\
   SS_SPY_MESSAGE(SS_DOMAINS_RECEIVED_REPORT)\
   SS_SPY_MESSAGE(SS_SPY_ON_DOMAIN)\
   \
   SS_SPY_MESSAGE(SS_DISABLE_MSG_LOGGING)\
   SS_SPY_MESSAGE(SS_ENABLE_MSG_LOGGING)\
   SS_SPY_MESSAGE(SS_QUERY_LOG_SETTINGS)\
   SS_SPY_MESSAGE(SS_SET_MAX_PAYLOAD_TO_LOG)\
   \
   SS_SPY_MESSAGE(SS_DUMP_CLIENT_STATS)\
   SS_SPY_MESSAGE(SS_CLIENT_STATS_DONE)\
   \
   SS_SPY_MESSAGE(SS_DISABLE_JSON_LOGGING)\
   SS_SPY_MESSAGE(SS_ENABLE_JSON_LOGGING)\
   SS_SPY_MESSAGE(SS_QUERY_JSON_LOG_SETTINGS)\
/**@verbatim                                                                   \
 * SS_JSON_SPY_TO_FROM_QUERY causes SocketServer to generate a                 \
 * SS_JSON_SPY_TO_FROM_REPORT response message.                                \
 *                                                                             \
 * Message Data Field: SS_JSON_SPY_TO_FROM_QUERY (code = SS_SPY)               \
 *                                                                             \
 * Message Payload: JSON string containing the following key/value pairs       \
 *   (NOTE - order is unspecified)                                             \
 *                                                                             \
 * --------------------------------------------------------------------------- \
 * KEY:          spy_uid                                                       \
 * VALID VALUES: Any valid UID.                                                \
 * PRESENCE:     REQUIRED                                                      \
 * DESCRIPTION:  UID of client for which the report is to be generated.        \
 * --------------------------------------------------------------------------- \
 *@endverbatim*/                                                               \
 SS_SPY_MESSAGE(SS_JSON_SPY_TO_FROM_QUERY)                                     \
/**@verbatim                                                                   \
 * SS_JSON_SPY_TO_FROM_REPORT is generated in response to a                    \
 * SS_JSON_SPY_TO_FROM_QUERY. Depending on the options in the query message,   \
 * this report is either directly sent to the client specified in the query or \
 * is broadcast.                                                               \
 *                                                                             \
 * Message Data Field: SS_JSON_SPY_TO_FROM_REPORT (code = SS_SPY_RESPONSE)     \
 *                                                                             \
 * Message Payload: JSON string containing the following key/value pairs       \
 *   (NOTE - order is unspecified)                                             \
 *                                                                             \
 * --------------------------------------------------------------------------- \
 * KEY:          spy_uid                                                       \
 * VALID VALUES: Any valid UID.                                                \
 * PRESENCE:     REQUIRED                                                      \
 * DESCRIPTION:  UID of client for which the report is to be generated.        \
 * --------------------------------------------------------------------------- \
 * KEY:          from                                                          \
 * VALID VALUES: Array of zero or more UIDs                                    \
 * PRESENCE:     Always present                                                \
 * DESCRIPTION:  Numeric value of UIDs that spy_uid is spying on messages FROM.\
 * --------------------------------------------------------------------------- \
 * KEY:          to                                                            \
 * VALID VALUES: Array of zero or more UIDs                                    \
 * PRESENCE:     Always present                                                \
 * DESCRIPTION:  Numeric value of UIDs that spy_uid is spying on messages FROM.\
 * --------------------------------------------------------------------------- \
 *@endverbatim*/                                                               \
SS_SPY_MESSAGE(SS_JSON_SPY_TO_FROM_REPORT)                                     \
/**@verbatim                                                                   \
 * SS_JSON_SPY_TO_FROM_ADD_CLIENTS causes SocketServer to add specified        \
 * clients to those whose incoming/outgoing messages are being spied upon by   \
 * the specified client.                                                       \
 *                                                                             \
 * Message Data Field: SS_JSON_SPY_TO_FROM_ADD_CLIENTS (code = SS_SPY)         \
 *                                                                             \
 * Message Payload: JSON string containing the following key/value pairs       \
 *   (NOTE - order is unspecified)                                             \
 *                                                                             \
 * --------------------------------------------------------------------------- \
 * KEY:          spy_uid                                                       \
 * VALID VALUES: Any valid UID.                                                \
 * PRESENCE:     REQUIRED                                                      \
 * DESCRIPTION:  UID of client for which the report is to be generated.        \
 * --------------------------------------------------------------------------- \
 * KEY:          replace                                                       \
 * VALID VALUES: true, false                                                   \
 * PRESENCE:     OPTIONAL                                                      \
 * DESCRIPTION:  If true, the spy lists are cleared prior the listed clients.  \
 * --------------------------------------------------------------------------- \
 * KEY:          from_uids                                                     \
 * VALID VALUES: array of zero or more client UIDs                             \
 * PRESENCE:     OPTIONAL                                                      \
 * DESCRIPTION:  The array contains a list of zero or more numbers that are    \
 *               the UIDs of clients to be added to the list of clients whose  \
 *               outgoing messages are being spied upon by the spy_uid.        \
 * --------------------------------------------------------------------------- \
 * KEY:          to_uids                                                       \
 * VALID VALUES: array of zero or more client UIDs                             \
 * PRESENCE:     OPTIONAL                                                      \
 * DESCRIPTION:  The array contains a list of zero or more numbers that are    \
 *               the UIDs of clients to be added to the list of clients whose  \
 *               incoming messages are being spied upon by spy_uid.            \
 * --------------------------------------------------------------------------- \
 *@endverbatim*/                                                               \
SS_SPY_MESSAGE(SS_JSON_SPY_TO_FROM_ADD_CLIENTS)                                \
/**@verbatim                                                                   \
 * SS_JSON_SPY_TO_FROM_REMOVE_CLIENTS causes SocketServer to remove specified  \
 * clients from the lists of those whose incoming/outgoing messages are being  \
 * spied upon by the specified client.                                         \
 *                                                                             \
 * Message Data Field: SS_JSON_SPY_TO_FROM_REMOVE_CLIENTS (code = SS_SPY)      \
 *                                                                             \
 * Message Payload: JSON string containing the following key/value pairs       \
 *   (NOTE - order is unspecified)                                             \
 *                                                                             \
 * --------------------------------------------------------------------------- \
 * KEY:          spy_uid                                                       \
 * VALID VALUES: Any valid UID.                                                \
 * PRESENCE:     REQUIRED                                                      \
 * DESCRIPTION:  UID of client for which the report is to be generated.        \
 * --------------------------------------------------------------------------- \
 * KEY:          remove_all                                                    \
 * VALID VALUES: true, false                                                   \
 * PRESENCE:     OPTIONAL                                                      \
 * DESCRIPTION:  If true, the outgoing spy list of the sender is cleared.      \
 * --------------------------------------------------------------------------- \
 * KEY:          from_uids                                                     \
 * VALID VALUES: array of zero or more client UIDs                             \
 * PRESENCE:     OPTIONAL                                                      \
 * DESCRIPTION:  The array contains a list of zero or more numbers that are    \
 *               the UIDs of clients to be removed the list of clients whose   \
 *               outgoing messages are being spied upon by spy_uid.            \
 * --------------------------------------------------------------------------- \
 * KEY:          to_uids                                                       \
 * VALID VALUES: array of zero or more client UIDs                             \
 * PRESENCE:     OPTIONAL                                                      \
 * DESCRIPTION:  The array contains a list of zero or more numbers that are    \
 *               the UIDs of clients to be removed the list of clients whose   \
 *               incoming messages are being spied upon by spy_uid.            \
 * --------------------------------------------------------------------------- \
 *@endverbatim*/                                                               \
SS_SPY_MESSAGE(SS_JSON_SPY_TO_FROM_REMOVE_CLIENTS)                             \


#undef  SS_SPY_MESSAGE
#define SS_SPY_MESSAGE(msg) msg,
/**
 * Create enum tags with the SPY message names.
 */
typedef enum
{
   SS_SPY_MESSAGES
   SS_NUM_SPY_MESSAGES
}
SS_Spy_Message_Data_T;

/*===========================================================================*/
/*!
 * @file ss_interface.h
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 19-Nov-2013 Kirk Bailey REV 4, 5
 *   - Added support for multiple to/from spy clients.
 *
 * - 17-Feb-2014 Kirk Bailey Rev 7
 *   - Added logic to guarantee we have an active connection to the server.
 *
 * - 17-Sep-2014 Joel Kiger Rev 8
 *  - Task kok_inf#12200 Fix SSL, add SSL configuration and add better error messages
 */
/*===========================================================================*/
/** @} doxygen end group */
#endif /* SS_INTERFACE_H */

