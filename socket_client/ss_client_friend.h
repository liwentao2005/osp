#ifndef SOCKET_CLIENT_FRIEND_H
#   define SOCKET_CLIENT_FRIEND_H
/*===========================================================================*/
/**
 * @file ss_client_friend.h
 *
 *   Declares the "friend" interface to the SocketServer Client Library.
 *
 * %full_filespec:ss_client_friend.h~1:incl:ctc_ec#4 %
 * @version %version:1 %
 * @author  %derived_by:bz08fr %
 * @date    %date_modified:Mon Feb 29 13:40:39 2016 %
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
#   include <arpa/inet.h>
#   include <pthread.h>
#   include "socket_client_api.h" /* Declares SS_ENABLE_SSL */

#   ifdef SS_ENABLE_SSL
#      error "SS_ENABLE_SSL not specified"
#   elif SS_ENABLE_SSL != 0
#      include <openssl/bio.h>
#      include <openssl/err.h>
#      include <openssl/ssl.h>
#   endif

/*
 * The following checks insure that the compile-time SS_ENABL_SSL option matches
 * the link-time SS_USE_SSL_LIB option.
 */
#   if defined(SS_USE_SSL_LIB) && (SS_ENABLE_SSL == 0)
#      error SS_USE_SSL_LIB indicates SSL library to be used; however, SS_ENABLE_SSL is zero.
#   endif /* if defined(XSAL_LIB) */
#   if !defined(SS_USE_SSL_LIB) && (SS_ENABLE_SSL != 0)
#      error SS_USE_SSL_LIB is not defined; however, SS_ENABLE_SSL is non-zero.
#   endif /* if defined(XSAL_LIB) */

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */
/*===========================================================================*
 * Exported Preprocessor #define Constants
 *===========================================================================*/

/**
 * This constant is the initially allocated message buffer.
 */
#   define SCA_INITIAL_MESSAGE_SIZE (1024)

#   define SCA_CONTEXT_PATTERN 0x5aa5a55a

/**
 * This constant can be made non-zero to print out details of what is happening
 */
#ifndef SCA_VERBOSE
# define SCA_VERBOSE (0)
#endif

#ifndef SS_DBC_PATH
/**
 * Defines the path and common part of the name of the file used to save the
 * dbg_trace levels.
 */
#   define SS_DBC_PATH "/var/.dbg_trace_lvls_"
#endif

/*===========================================================================*
 * Exported Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/
typedef struct SCA_Subscribe_Data_Tag
{
   uint32_t code;
   bool_t   enable_report;
}
SCA_Subscribe_Data_T;

/**
 * This type represents a socket server client
 */
struct SCA_Client_Instance_Tag
{
      uint32_t valid_pattern;
      pthread_mutex_t send_lock; /** Used to make sends thread-safe. */
      int socket_ref;         /** Socket file descriptor */
      int connect_result;     /** -1 if call to connect() failed */
      //SCA_Connection_State_T connection_state; /** Current state of the connection to the SocketServer*/
      int read_error_occured; /** Non-zero if a read error occured last time we tried */
      struct sockaddr_in socket_adr; /** Socket connect() info */
      SCA_Socket_Client_Unique_ID_T uid; /** Client 4-char unique ID */
      char *rd_buffer;
      size_t rd_buffer_size;
      pthread_mutex_t instance_mutex; /** Mutex for manipulating instance in multiple threads */
      sem_t start_stop_sem;           /** Semaphore used to sync startup/shutdown */
      //blocklist* subscription_list;   /** List of SCA_Subscribe_Data_T for subscribed messages */
      void* callback;
      void* context;
      char *dbg_ctrl_path; /**< Path for dbg_ctrl persistent data */
      pthread_t thread_id;
      void* connection_info_callback; /**< client implementer provided function called when the connection state changes */
      char uid_str[sizeof(SCA_Socket_Client_Unique_ID_T) + 1]; /* String for UID display */
      bool_t is_ssl_client;
      char inet_addr_string[INET_ADDRSTRLEN]; /**< buffer used to create a printable ip address */
      sem_t connect_semaphore; /**triggers when connect is complete*/
#if SS_ENABLE_SSL != 0
      char const *passphrase;
      char const *cert_file;
      char const *key_file;
      bool_t m_is_shutdown;
      SSL *m_ssl;
      SSL_CTX *m_ssl_ctx;
      BIO *m_bio;
#endif
};

/*===========================================================================*
 * Exported Const Object Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Exported Inline Function Definitions and #define Function-Like Macros
 *===========================================================================*/

/* MACRO to lock a mutex with logging and error checking */
#define SCA_Lock_Mutex(m)\
   do {\
      int mutex_err;\
      SCA_DEBUG_0("Attempting to lock mutex " #m);\
      mutex_err = pthread_mutex_lock(&m);\
      if (mutex_err != 0) { SCA_ERR_1("pthread_mutex_lock(" #m ") FAILED: %s", strerror(mutex_err)); }\
      else { SCA_DEBUG_0("Lock " #m " Acquired"); }\
   } while (0)

#define SCA_Signal_Condvar(c)\
   do {\
      int condvar_err;\
      SCA_DEBUG_0("Signalling " #c );\
      condvar_err = pthread_cond_signal(&c);\
      if (condvar_err != 0) { SCA_ERR_1("pthread_cond_signal(" #c ") FAILED: %s", strerror(condvar_err)); }\
      else { SCA_DEBUG_0(#c " was signalled"); }\
   } while (0)

/* MACRO to unlock a mutex with logging and error checking */
#define SCA_Unlock_Mutex(m)\
   do {\
      int mutex_err;\
      SCA_DEBUG_0("Unlocking mutex " #m );\
      mutex_err = pthread_mutex_unlock(&m);\
      if (mutex_err != 0) { SCA_ERR_1("pthread_mutex_unlock(" #m ") FAILED: %s", strerror(mutex_err)); }\
      else { SCA_DEBUG_0("Lock " #m " Released");}\
   } while (0)

#define SCA_Wait_For_Condvar(c,m)\
   do {\
      int condvar_err;\
      SCA_DEBUG_0("Waiting on " #c );\
      condvar_err = pthread_cond_wait(&c,&m);\
      if (condvar_err != 0) { SCA_ERR_1("pthread_cond_wait(" #c ") FAILED: %s", strerror(condvar_err)); }\
      else { SCA_DEBUG_0("Wait on " #c " ended"); }\
   } while (0)

/**
 * These macros are used for debugging
 */
#if SCA_VERBOSE
# define SCA_DEBUG_0(a)     Tr_Info_Lo_1("[%s] " a, (instance ? instance->uid_str:"NULL"))
# define SCA_DEBUG_1(a,b)   Tr_Info_Lo_2("[%s] " a, (instance ? instance->uid_str:"NULL"), b)
# define SCA_DEBUG_2(a,b,c) Tr_Info_Lo_3("[%s] " a, (instance ? instance->uid_str:"NULL"), b, c)
#else
# define SCA_DEBUG_0(a)
# define SCA_DEBUG_1(a,b)
# define SCA_DEBUG_2(a,b,c)
#endif

#define SCA_ERR_NULL(a, b)  Tr_Fault_1(a, b)
#define SCA_ERR_0(a)     /*Tr_Fault_1("[%s] " a, (instance ? instance->uid_str:"NULL"))*/
#define SCA_ERR_1(a,b)   /*Tr_Fault_2("[%s] " a, (instance ? instance->uid_str:"NULL"), b)*/
#define SCA_ERR_2(a,b,c) /*Tr_Fault_3("[%s] " a, (instance ? instance->uid_str:"NULL"), b, c)*/

#ifdef __cplusplus
}
#endif
/*===========================================================================*/
/*!
 * @file ss_client_friend.h
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 11-Sep-2013 Kirk Bailey
 *   - Added standard comment blocks, including this history block.
 *
 * - 18-Sep-2013 Kirk Bailey
 *   - Made SocketServer use of OpenSSL library configurable.
 *
 * - 30-Sep-2013 Kirk Bailey
 *   - Added dbg_ctrl_path to client context for dbg_trace logic.
 *
 * - 04-Oct-2013 Kirk Bailey Rev 6
 *   - Added ability to register a callback to obtain connection status.
 *
 * - 09-Oct-2013 Kirk Bailey Rev 7,8
 *   - Fixed MACROs to handle NULL instance.
 *
 * - 17-Feb-2014 Kirk Bailey Rev 9
 *   - Renamed semaphore to start_stop_sem.
 *
 * - 12-Feb-2015 Joel Kiger Rev 10
 *  - Task kok_inf#19931 Performance improvements to connect process
 */
/*===========================================================================*/
/** @} doxygen end group */
#endif /* SOCKET_CLIENT_FRIEND_H */
