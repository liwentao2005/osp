#ifndef SS_CLIENT_BASE_API_H
#define SS_CLIENT_BASE_API_H

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */

/*===========================================================================*
 * Exported Type Declarations
 *===========================================================================*/
typedef struct SC_Message_S
{
	unsigned int code;		 /** The "message ID" code */
	unsigned int data;		 /** 32-bits of data */
	unsigned int payload_size; /** length of payload in bytes */
	char payload[1];		 /** This DYNAMIC field MUST BE LAST */
} SC_Message_T;

/* definition of data structure for share memory block*/
typedef struct SClt_NameStore_s
{
	char name_idex[128];
}SClnt_NameStore_t;

#define  SHAMEMROY_BASENAME    "SSClient_Name_Store"

#define  SOCKETSERVER_CLIENT_NAME    "examp"

int SSClient_Name_Generator(char *Base_Nam, char *Client_Nam, int Client_Name_size);
unsigned int Init_SocketServer_Client_Defult(char *Client_Name, void* CallBack);

void Launch_SocketServer_Client(unsigned int Client_ID);
int  SocketServer_Client_Send(unsigned int Client_ID,  char *receiver_name, unsigned int message_id, unsigned int data, void *payload, unsigned int payload_size);

#   ifdef __cplusplus
} /* extern "C" */
#   endif /* __cplusplus */

#endif