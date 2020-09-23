#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>


#include "ss_client_base_api.h"
#include "socket_client_api.h"




/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/



/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

#define SS_DEFAULT_APP_NAME "samp"

#define SS_DEFAULT_IP_ADRS "127.0.0.1"

#define SS_DEFAULT_PORT "1255"


#define SS_IP_ADRS_LEN  16


/** File that can be used to specify another SocketServer address. */
#define SS_IP_ADRS_FILE "/var/socket_server_ip"

/** File that can be used to specify another SocketServer port. */
#define SS_PORT_FILE    "/var/socket_server_port"

/** Variable is set when the program should exit */
/*volatile bool_t Exit_Requested = false;*/





typedef struct SS_Client_Info_S
{
	unsigned int           		Port;
	unsigned int           		Application_UID;
	char                   		*Ip_Address;
	//SCA_Client_Instance_T 		*Application_Instance;
	char                   		Name[16];
	//SCA_Message_Callback_T 		RcvMsg_CallBack;
	struct  SS_Client_Info_S	*pNext;
	struct  SS_Client_Info_S	*pPrev;
	//bool  					Exit_Requested;
}SS_Client_Info_T;


SS_Client_Info_T *SS_Client_List;

pthread_mutex_t	  SS_Client_Mutex;

unsigned long Str2ID(const char* name)
{
	unsigned long s, i;
    for (s = i = 0; name[i]; i++)
		s = (s + (i + 1) * name[i]) % 0x8000000bu * 0xffffffefu;
	return s ^ 0x12345678;
}

int SSClient_Name_Generator(char *Base_Nam, char *Client_Nam, int Client_Name_size)
{

	int     i;
	int     sem_id;
	char    ShaMem_Nam[64]={0};
	int 	isNew = 0;
   	int 	fd = -1;

	SClnt_NameStore_t  *pSClient_NamStore;

	if(Base_Nam == NULL || strlen(Base_Nam) != 2 || Client_Nam == NULL || Client_Name_size < 5)
	{
		return -1;
	}
	
	snprintf(ShaMem_Nam, sizeof(ShaMem_Nam), "%s_%s" ,SHAMEMROY_BASENAME, Base_Nam);
    /*create*/
	fd = shmget(Str2ID(ShaMem_Nam), sizeof(SClnt_NameStore_t), IPC_CREAT | IPC_EXCL | 0666);
	if(-1 == fd)
	{
		printf("%s sharememory already exist!\n", ShaMem_Nam);
		fd = shmget(Str2ID(ShaMem_Nam), sizeof(SClnt_NameStore_t), IPC_CREAT | 0666);
		if (fd < 0)
		{
			printf("%s sharememory get failed\n", ShaMem_Nam);
			//Unlock_SSC_Sem(sem_id);
			return -1;
		}
		
		isNew=0;
	}
	else
	{
		printf("creat a new %s sharememory!\n", ShaMem_Nam);
		isNew=1;
	}
	
	/*mapping*/
	pSClient_NamStore = (SClnt_NameStore_t *)shmat(fd, NULL, 0);
	if(NULL == pSClient_NamStore)
	{
		printf("%s sharememory mapping failed \n",ShaMem_Nam);
		//Unlock_SSC_Sem(sem_id);
		return -1;
	}

	/*if it is new created, clean it*/
	if(isNew)
	{
		memset(pSClient_NamStore->name_idex, 0, sizeof(pSClient_NamStore->name_idex));
	}
  
	for(i=0;i<sizeof(pSClient_NamStore->name_idex);i++ )
	{
		if(pSClient_NamStore->name_idex[i]== 0)
		{
			pSClient_NamStore->name_idex[i] = 1;
			break;
		}
	}
   
	if(i<10)
	{
		snprintf(Client_Nam, 5, "%s%d%d", Base_Nam, 0,i);
	}
	else
	{
		snprintf(Client_Nam, 5, "%s%d", Base_Nam, i);
	}

	return 0;
	
}
