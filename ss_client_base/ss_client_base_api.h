#ifndef SS_CLIENT_BASE_API_H
#define SS_CLIENT_BASE_API_H

#   ifdef __cplusplus
extern "C"
{ /* ! Inclusion of header files should NOT be inside the extern "C" block */
#   endif /* __cplusplus */

/* definition of data structure for share memory block*/
typedef struct SClt_NameStore_s
{
	char name_idex[128];
}SClnt_NameStore_t;

#define  SHAMEMROY_BASENAME    "SSClient_Name_Store"

#define  SOCKETSERVER_CLIENT_NAME    "examp"

int SSClient_Name_Generator(char *Base_Nam, char *Client_Nam, int Client_Name_size);

#   ifdef __cplusplus
} /* extern "C" */
#   endif /* __cplusplus */

#endif