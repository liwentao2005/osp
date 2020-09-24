#ifndef SOCKET_CLIENT_API_H
#define SOCKET_CLIENT_API_H

#include "reuse.h"

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */

/**
 * Anonymous types used to hold client context.
 */
struct SCA_Client_Instance_Tag
{
    //uint32_t valid_pattern;
    pthread_mutex_t send_lock; /** Used to make sends thread-safe. */
    int socket_ref;         /** Socket file descriptor */
    int connect_result;     /** -1 if call to connect() failed */
};
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

/*===========================================================================*
 * Exported Function Prototypes
 *===========================================================================*/

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

#   ifdef __cplusplus
} /* extern "C" */
#   endif /* __cplusplus */

#endif
