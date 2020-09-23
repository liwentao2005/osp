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
int SCA_Listen(SCA_Client_Instance_T* instance, SCA_Message_Callback_T callback)
{
    printf("%s--%d.\n", __FILE__, __LINE__);
   return 0;
}
