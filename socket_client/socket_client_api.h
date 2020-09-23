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
    //uint32_t payload_size; /** length of payload in bytes */
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
