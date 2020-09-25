#ifndef SOCKET_CLIENT_API_H
#define SOCKET_CLIENT_API_H

#include "reuse.h"
#include "ss_interface.h"
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */

/**
 * UID temporarily assigned between calls SCA_Create_Instance() and
 * SCA_Connect(). Use SCA_Create_Instance_With_UID() to eliminate this gap.
 */
#define SCA_UNKNOWN_UID SCA_FOURCC_TO_UID('?','?','?','?')

/*===========================================================================*
 * Exported Preprocessor #define MACROS
 *===========================================================================*/

/**
 * This macro converts a 4-character-code (a "fourcc" like 'DRVR' for "driver",
 * or 'MSTR' for "master") to the SCA_Socket_Client_Unique_ID_T type
 *
 * @return A uint32_t value that combines the four characters.
 * @param [in] a The most significant character.
 * @param [in] b The 2nd most significant character.
 * @param [in] c The 3rd most significant character.
 * @param [in] d The least significant character.
 *
 * Example Usage:
 *   SCA_Socket_Client_Unique_ID_T my_client_id = SCA_FOURCC_TO_UID('M','S','T','R');
 */
#   define SCA_FOURCC_TO_UID(a,b,c,d) SS_FOURCC_TO_UID(a,b,c,d)

/**
 * Anonymous types used to hold client context.
 */
struct SCA_Client_Instance_Tag;
typedef struct SCA_Client_Instance_Tag SCA_Client_Instance_T;

/**
 * This type represents a 4-character-code (a "fourcc" like 'DRVR' for "driver",
 *  or 'MSTR' for "master")
 *
 * @note This is *not* a C string - there is no NUL terminating character
 *
 * Example Usage:
 *   SCA_Socket_Client_Unique_ID_T my_client_id = SCA_FOURCC_TO_UID('D','R','V','R');
 */
typedef uint32_t SCA_Socket_Client_Unique_ID_T;

/**
 * This type represents an application message
 *
 * @note This structure is always malloc'ed, and the "payload" field may be
 *       arbitrarily long (not just 1 byte as the declaration below might lead
 *       one to believe)
 */
typedef struct SCA_Message_T_struct_tag
{
    uint32_t code;         /** The "message ID" code */
    uint32_t data;         /** 32-bits of data */
    uint32_t payload_size; /** length of payload in bytes */
    char payload[1];       /** This DYNAMIC field MUST BE LAST */
} SCA_Message_T;

/**
 * This type represents a callback function a client can use to receive
 * incoming messages.
 *
 * Example Usage:
 *   SCA_Message_Callback_T my_callback = \&my_message_handler;
 *   SCA_Listen(my_callback);
 */
typedef void (*SCA_Message_Callback_T)(SCA_Message_T const * const message);

/**
 * This type represents a callback function a client can use to receive
 * incoming messages
 *
 * Example Usage:
 *   SCA_Message_Context_Callback_T my_callback = \&my_message_handler;
 *   SCA_Listen_With_Context(my_callback, this);
 */
typedef void (*SCA_Message_Context_Callback_T)(SCA_Message_T const * const message, void* context);

/*===========================================================================*
 * Exported Function Prototypes
 *===========================================================================*/

/**
 * Anonymous types used to hold client context.
 */
struct SCA_Client_Instance_Tag;
typedef struct SCA_Client_Instance_Tag SCA_Client_Instance_T;

/**
 * This function converts the first 4-characters of "unique_fourcc_name"
 * (a "fourcc" like "DRVR" for "driver", or "MSTR" for "master") to the
 * SCA_Socket_Client_Unique_ID_T type, and returns it
 *
 * @return The UID result.
 *
 * @param unique_fourcc_name Pointer to string containing UID.
 *
 * Example Usage:
 *   SCA_Socket_Client_Unique_ID_T my_client_id = SCA_Convert_String_To_UID("MSTR");
 */
SCA_Socket_Client_Unique_ID_T SCA_Convert_String_To_UID(char const * const unique_fourcc_name);

/**
 * Converts a UID to a string of 4 printable characters followed by a NUL terminator;
 * the function will not write beyond the specified buffer boundaries and will
 * guarantee a NUL terminator.
 *
 * @param uid      The UID value to be converted.
 * @param buf      Pointer to where first character is to be written.
 * @param buf_size Number of char slots available starting at 'buf';
 *                           this should be at least 5 for the result to not be
 *                           truncated.
 *
 * Example Usage:
 *     char uid_str[5];
 *     SCA_UID_To_String(uid, uid_str, sizeof(uid_str));
 */
void SCA_UID_To_String(uint32_t uid, char *buf, size_t buf_size);

/**
 * @return The version string for the SS client library.
 */
char const *SCA_Get_Version(void);

/**
 * DEPRECATED - Use SCA_Create_Instance_With_UID() instead!
 *
 * Creates a client instance and sets the desired UID to "????"; this call is
 * only present for backwards compatibility. Older clients create an instance
 * with this call and then later establish the UID with the SCA_Connect() call.
 * Now that persistent dbg_trace levels are supported for clients, the UID is
 * used to form the name of the file used for the client's trace level settings.
 * The sooner this information is known, the sooner the trace levels can be
 * initialized. For older clients, this won't happen until SCA_Connect() is
 * called. For clients that use SCA_Create_Instance_With_UID(), the levels
 * will be set when that call is made.
 *
 * @return A pointer to an initialized instance variable to be used with
 *         all other calls pertaining to this client.
 *
 * @note The caller is responsible for calling SCA_Destroy_Instance() when it
 *       is through with the instance; failure to do so will cause a leak.
 */
#define SCA_Create_Instance() SCA_Create_Instance_With_UID(SCA_UNKNOWN_UID)

/**
 * Creates and initializes an SCA_Client_Instance_T that can be used to identify
 * a client and establishes the "desired" UID of the client. The type created is
 * anonymous to the caller so that it does not become coupled to a specific
 * implementation. An instance variable is required to keep track of the
 * client's state. Multiple instances can be created within a process thereby
 * allowing multiple clients to be controlled via that process.
 *
 * The specified unique_id is the "desired" one in the sense that a UID is only
 * assigned by SocketServer upon connection. It is possible for the desired UID
 * to be rejected by SocketServer if another client has already claimed that
 * UID. Specifying the UID at the time the instance is created allows the
 * persistent dbg_trace levels to be loaded earlier in the process.
 *
 * @return A pointer to an initialized instance variable to be used with
 *         all other calls pertaining to this client.
 *
 * @param unique_id The UID that this client wishes to obtain from SocketServer
 *                  when it establishes a connection.
 *
 * @note The caller is responsible for calling SCA_Destroy_Instance() when it
 *       is through with the instance; failure to do so will cause a leak.
 */
SCA_Client_Instance_T *SCA_Create_Instance_With_UID(SCA_Socket_Client_Unique_ID_T unique_id);

/**
 * This function sets up a thread to call "callback" function when messages
 * arrive for the client
 *
 * @return 0 for success, -1 if socket is not yet open.
 *
 * @param instance  Pointer to client instance data.
 * @param     callback  Function to call and pass received messages to
 *
 * Example Usage:
 *   SCA_Listen(&instance, &my_message_handler);
 */
int SCA_Listen(SCA_Client_Instance_T* instance, SCA_Message_Callback_T callback);

/**
 * This function sets up a thread to call "callback" function when messages
 * arrive for the client
 *
 * @return 0 for success, -1 if socket is not yet open.
 *
 * @param instance  Pointer to client instance data.
 * @param     callback  Function to call and pass received messages to
 * @param context   Pointer to client-specific data context ("this" pointer).
 *
 * Example Usage:
 *   SCA_Listen(&instance, &my_message_handler, this);
 */
int SCA_Listen_With_Context(SCA_Client_Instance_T* instance,
                            SCA_Message_Context_Callback_T callback,
                            void* context);

#   ifdef __cplusplus
} /* extern "C" */
#   endif /* __cplusplus */

#endif
