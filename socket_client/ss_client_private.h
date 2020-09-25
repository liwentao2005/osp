#ifndef SOCKET_CLIENT_PRIVATE_H
#   define SOCKET_CLIENT_PRIVATE_H
/*===========================================================================*/
/**
 * @file ss_client_private.h
 *
 *   Global declarations that are private to the SSC library.
 *
 * %full_filespec:ss_client_private.h~1:incl:ctc_ec#4 %
 * @version %version:1 %
 * @author  %derived_by:bz08fr %
 * @date    %date_modified:Mon Feb 29 13:40:53 2016 %
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
 * @section ABBR ABBREVIATIONS:
 *   - SS = SocketServer
 *   - SCA = SocketServer Client API
 *   - SSC = SocketServer Client
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *
 *   - Requirements Document(s):
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - None
 *
 * @ingroup SSC_Library
 * @{
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#   include "ss_client_friend.h"

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */
/*===========================================================================*
 * Exported Preprocessor #define Constants
 *===========================================================================*/

/*===========================================================================*
 * Exported Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Const Object Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Function Prototypes
 *===========================================================================*/

/**
 * Performs any configuration unique to a secure connection.
 *
 * @param instance  Pointer to client instance data.
 */
void sca_Configure_SSL_Socket(SCA_Client_Instance_T* instance);
/**
 * Performs any cleanup unique to a secure connection.
 *
 * @param instance  Pointer to client instance data.
 */
void sca_Destroy_SSL_Context(SCA_Client_Instance_T* instance);
/**
 * Closes the current connection and sets the connection state to "connecting".
 *
 * @param instance  Pointer to client instance data.
 */
void sca_Disconnect_On_Err(SCA_Client_Instance_T* instance);
/**
 * Checks the client instance to make sure it is valid.
 *
 * @return true if valid; false otherwise.
 *
 * @param func_name Pointer to string with name of function that is
 *                       making the call (for logging purposes).
 * @param instance  Pointer to client instance data.
 */
bool_t sca_Instance_Is_Valid_Func(char const *func_name, SCA_Client_Instance_T* instance);
/**
 * Handles messages that are automatically taken care of for all clients, like
 * SOH, debug control, etc.
 *
 * @return true if this was a local message handled by this function; false otherwise.
 *
 * @param instance  Pointer to client instance data.
 * @param destination UID to which message was sent
 * @param code Message code.
 * @param data Message data.
 * @param payload_size Size of message payload.
 * @param payload Pointer to message payload.
 */
bool_t sca_Process_Local_Message(SCA_Client_Instance_T* instance, uint32_t destination,
                                 uint32_t code, uint32_t data, size_t payload_size, char const* payload);

/**
 * This function sends an application message to SocketServer, SocketServer will forward the
 * application message to "destination".
 *
 * If "destination" is 0x00000000, then it is a control message for SocketServer, and
 * SocketServer will not forward the message
 *
 * If "destination" is 0xFFFFFFFF, then it is a broadcast message, and SocketServer will
 * forward the message to any/all clients that have subscribed to it
 *
 * @return zero on success; -1 otherwise.
 *
 * @param instance  Pointer to client instance data.
 * @param destination UID to which message was sent
 * @param code Message code.
 * @param data Message data.
 * @param payload Pointer to message payload.
 * @param payload_size Size of message payload.
 */
int sca_Send_Message(SCA_Client_Instance_T* instance,
                     SCA_Socket_Client_Unique_ID_T destination,
                     uint32_t code, uint32_t data,
                     void const * const payload, size_t payload_size);
/**
 * Performs any connection shutdown logic unique to a secure connection.
 *
 * @param instance  Pointer to client instance data.
 */
void sca_Shutdown_SSL(SCA_Client_Instance_T* instance);

/**
 * Writes a message out to a secure connection.
 *
 * @return 0 for success; -1 for failure.
 *
 * @param instance  Pointer to client instance data.
 * @param wr_hdr   Pointer to message header
 * @param payload  Pointer to payload (if any) for message.
 * @param payload_size  Size of message payload (must be zero if payload is NULL).
 */
int sca_Write_Message_SSL(SCA_Client_Instance_T* instance,
                          SS_Message_Header_T const * wr_hdr,
                          void const * const payload, size_t payload_size);

/**
 * Reads a message from a secure connection.
 *
 * @return bytes read; <= 0 for failure.
 *
 * @param instance  Pointer to client instance data.
 * @param buf       Buffer to read into
 * @param len       Length to read
 */
int sca_Read_Socket_SSL(SCA_Client_Instance_T* instance,void *buf,size_t len);

/*===========================================================================*
 * Exported Inline Function Definitions and #define Function-Like Macros
 *===========================================================================*/

/**
 * Checks the client instance to make sure it is valid.
 *
 * @return true if valid; false otherwise.
 *
 * @param instance  Pointer to client instance data.
 */
#define sca_Instance_Is_Valid(instance) sca_Instance_Is_Valid_Func(__func__, instance)

#   ifdef __cplusplus
}         /* extern "C" */
#   endif /* __cplusplus */
/*===========================================================================*/
/*!
 * @file ss_client_private.h
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 11-Sep-2013 Kirk Bailey
 *   - Created initial file.
 *
 * - 30-Sep-2013 Kirk Bailey
 *   - Made "Send_Message" global to implemented dbg_ctrl logic.
 *
 * - 17-Sep-2014 Joel Kiger Rev 3
 *  - Task kok_inf#12290 Remove blocking for ssl_accept and fix valgrind errors
 */
/*===========================================================================*/
/** @} doxygen end group */
#endif /* SOCKET_CLIENT_PRIVATE_H */



