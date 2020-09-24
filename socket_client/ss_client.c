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

int func_cnt = 0;
int now_flag = 0;

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
int SCA_Listen(SCA_Client_Instance_T *instance, SCA_Message_Callback_T callback)
{
    printf("%s--%d.\n", __FILE__, __LINE__);
    return 0;
}
