#include "Socket_Server_T.hpp"
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/** Identify module for dbg_trace. */

#define ARG_LIST "def::hj:r:m:np:Vzsb:"

#define SS_DEFAULT_PORT "1255"
#define SS_PORT_FILE "/var/socket_server_port"
#define SS_DEFAULT_LOG_FILE "SocketServer.log"
#define SS_DEFAULT_LOG_FILE_SIZE (5242880)

static unsigned short SS_Port_Number = 1255;
static char * SS_JSON_Log_File = NULL;
static size_t SS_JSON_Log_Size = SS_DEFAULT_LOG_FILE_SIZE;
static Socket_Server_T *SS_Server;
int main(int argc, char *argv[])
{
   unsigned short non_secure_port;
   unsigned short secure_port;
   SS_Server = new Socket_Server_T(non_secure_port, secure_port, SS_JSON_Log_File, SS_JSON_Log_Size);

   if (NULL == SS_Server)
   {
      //Tr_Cpp_Fault("Failed to create Socket_Server_T instance - terminating");
      exit(-1);
   }
   SS_Server->Run();

   delete SS_Server;
   SS_Server = NULL;
   return 0;
}
