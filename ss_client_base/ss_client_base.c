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
	SCA_Client_Instance_T 		*Application_Instance;
	char                   		Name[16];
	SCA_Message_Callback_T 		RcvMsg_CallBack;
	struct  SS_Client_Info_S	*pNext;
	struct  SS_Client_Info_S	*pPrev;
	bool_t  					Exit_Requested;
}SS_Client_Info_T;


SS_Client_Info_T *SS_Client_List;

pthread_mutex_t	  SS_Client_Mutex;


int32_t  Add_SSClient_To_List(SS_Client_Info_T *client)
{
	SS_Client_Info_T  *pTmp;

	pthread_mutex_lock(&SS_Client_Mutex);

/*	printf("Add_SSClient_To_List SS_Client_List=0x%x  client=%x\n",SS_Client_List,client);*/
	
	if(NULL==SS_Client_List)                    					 
	{
		pTmp=client;
		pTmp->pPrev=NULL;
		pTmp->pNext=NULL;
		SS_Client_List=pTmp;
	} 
	else
	{	
		pTmp=SS_Client_List;

		while(NULL!=pTmp->pNext)
		{
		   pTmp=pTmp->pNext;
		}

		pTmp->pNext=client;
		pTmp->pNext->pNext=NULL;
		pTmp->pNext->pPrev=pTmp;

	}
    pthread_mutex_unlock(&SS_Client_Mutex);
	
	return 0;
}


int32_t  Del_SSClient_Frm_List(uint32_t  client_ID)
{
	SS_Client_Info_T  *pTmp;
	SS_Client_Info_T  *pCurp;

	pthread_mutex_lock(&SS_Client_Mutex);
	
	pCurp=SS_Client_List;
/*	printf("Del_SSClient_Frm_List pTmp=0x%x\n",pTmp);*/
	while(NULL != pCurp)
	{
	
		pTmp = pCurp;
/*		printf("Del_SSClient_Frm_List pTmp->Application_UID = %d  pTmp->next = 0x%x \n", pTmp->Application_UID, pTmp->pNext );*/
		if(pTmp->Application_UID == client_ID)
		{
			
			if(NULL==pTmp->pPrev) 
			{
				if(NULL != pTmp->pNext)
				{
					SS_Client_List =  pTmp->pNext;					
				}
				else
				{				
					SS_Client_List = NULL;
				}

			}
			else
			{
				if(NULL != pTmp->pNext)
				{
					pTmp->pPrev->pNext = pTmp->pNext;
					pTmp->pNext->pPrev = pTmp->pPrev;
				}
				else
				{
					pTmp->pPrev->pNext = NULL;
				}
			
			}
			pCurp=NULL;
			free(pTmp);
			
		}
		else
		{
			pCurp=pTmp->pNext;
		}
		
	}
	
    pthread_mutex_unlock(&SS_Client_Mutex);
	
	return 0;
}


SS_Client_Info_T*  Get_SSClient_Frm_List(unsigned int  client_ID)
{
   SS_Client_Info_T  *pTmp;

   pthread_mutex_lock(&SS_Client_Mutex);

   pTmp=SS_Client_List;

   while(pTmp)
   {
/*	   printf("Get_SSClient_Frm_List pTmp->Application_UID = %d  pTmp->next = %x \n", pTmp->Application_UID, pTmp->pNext );*/
		
	   if(pTmp->Application_UID == client_ID)
	   {
	      break;
		  
	   }
       else
       {
	   	  pTmp=pTmp->pNext;
       }
	 
   }

   pthread_mutex_unlock(&SS_Client_Mutex);

   return pTmp;
}


/*
 * Please see description in cfg_file_util.h
 */
void Free_Config_String(char const ** config_string)
{
   free((char *) *config_string);
   *config_string = NULL;
}


unsigned int Init_SocketServer_Client_Defult(char *Client_Name, void *CallBack)
{
	SS_Client_Info_T *client_instance = NULL;
	char const * port_str;

	unsigned int           		a_application_UID;
	if(Client_Name != NULL)
		a_application_UID = SCA_Convert_String_To_UID(Client_Name);
	else
		a_application_UID = SCA_Convert_String_To_UID(SS_DEFAULT_APP_NAME);
	
	client_instance = Get_SSClient_Frm_List(a_application_UID);
	
/*	printf("2 Init_SocketServer_Client_Defult a_application_UID=%d\n",a_application_UID);*/

	
	if(client_instance == NULL )
	{
		client_instance = malloc(sizeof(SS_Client_Info_T));

		if(NULL == client_instance)
		{
			printf("2 Init_SocketServer_Client_Defult malloc(sizeof(SS_Client_Info_T))  if failed   a_application_UID=%d\n",a_application_UID);
			return 0;
		}

		memset(client_instance, 0 , sizeof(SS_Client_Info_T));

		client_instance->Ip_Address = strdup(SS_DEFAULT_IP_ADRS);

		port_str = strdup(SS_DEFAULT_PORT);
		if (port_str != NULL)
		{
			client_instance->Port =(unsigned short)strtoul(port_str, NULL, 0);
			Free_Config_String(&port_str);
		}	
		else
		{
			client_instance->Port =(unsigned short)strtoul(SS_DEFAULT_PORT, NULL, 0);;
		}

       
		client_instance->Application_UID = a_application_UID;
		

		if(CallBack != NULL)
		{
		    client_instance->RcvMsg_CallBack = (SCA_Message_Callback_T)CallBack;
		}

		Add_SSClient_To_List(client_instance);
	}
	else
	{
		printf("2 Init_SocketServer_Client_Defult application_UID repeat \n");
		return a_application_UID;
	}


	return client_instance->Application_UID;
}

SCA_Client_Instance_T 	*Get_Client_App_Instance(unsigned int Client_ID)
{
	SS_Client_Info_T *SS_Client;


	SS_Client=Get_SSClient_Frm_List(Client_ID);
	if(SS_Client == NULL)
	{
		return NULL;
	}
	return SS_Client->Application_Instance;
}

void* ss_client_start(void *arg)
{ 
   uint32_t     client_ID;
   
   SS_Client_Info_T *client_instance=NULL;

   client_ID= *(uint32_t *)arg;

   client_instance=Get_SSClient_Frm_List(client_ID);
   
   if(client_instance == NULL)
   {
     printf("\n ss client instance does not exist !\n");
     return NULL;
   }

   printf("\n SocketServer Client library version %s\nOpening client socket connection as '%s' on '%s', port %d...\n",
          SCA_Get_Version(), client_instance->Name, client_instance->Ip_Address, client_instance->Port);

   client_instance->Application_Instance = SCA_Create_Instance();

   if(client_instance->Application_Instance == NULL)
   {
   	 printf("\n ss client application instance does not exist !\n");
     return NULL;
   }
   
   SCA_Listen(client_instance->Application_Instance,  client_instance->RcvMsg_CallBack);
   SCA_Connect(client_instance->Application_Instance, client_instance->Ip_Address, client_instance->Port, client_instance->Application_UID);
   while (!SCA_Is_Connected(client_instance->Application_Instance) && !client_instance->Exit_Requested)
   {
    #if 0 /* baodong.kan@20171114, shorter sleep time for fastboot */
      sleep(1);
    #else
      usleep(200*1000);
    #endif
   }

   printf("SocketSever_Client: %s           connect successfully\n",client_instance->Name);
 #if 0
   while (!client_instance->Exit_Requested)
   {
      /* Main loop of execution. The following sleep() is only for the template and probably should be removed. */
      sleep(1);
   }
	
   printf("ss client exit\n");
  
   SCA_Disconnect(client_instance->Application_Instance);

   SCA_Destroy_Instance(&client_instance->Application_Instance);

   Free_Config_String(&client_instance->Ip_Address);
   
   Destory_SocketServer_Client(client_instance->Application_UID);
 #endif
   return NULL;
}

void Launch_SocketServer_Client(unsigned int Client_ID)
{
	uint32_t      ClientID;
	
	ClientID=Client_ID;
	
   #if 0
    pthread_t	  SS_Client_Tid;
	CrtThread(&SS_Client_Tid, -1 , PTHREAD_CREATE_DETACHED, ss_client_start, &ClientID);
    usleep(10000);
   #else
   	ss_client_start(&ClientID);
   #endif
}

int SocketServer_Client_Send(unsigned int Client_ID,  char *receiver_name, unsigned int message_id, unsigned int data, void *payload, unsigned int payload_size)
{
	int res;
	SCA_Client_Instance_T *Application_Instance;
	unsigned int dst_uid;

	if(receiver_name == NULL)
    {
    	return -1;
    }
	
	Application_Instance=Get_Client_App_Instance(Client_ID);
	if(Application_Instance == NULL )
	{
		return -1;
	}
	
	dst_uid=SCA_Convert_String_To_UID(receiver_name);
	
	res=SCA_Send(Application_Instance, dst_uid, message_id, data, payload, payload_size);

	return res;
}

int  SocketServer_Client_CID_To_String(unsigned int Client_ID, char *NamBuf, unsigned int NamBuf_Size)
{
	if(NamBuf == NULL)
	{
		return -1;
	}

	memset(NamBuf, 0, NamBuf_Size);
	
	SCA_UID_To_String(Client_ID, NamBuf, NamBuf_Size);

	return 0;
}


unsigned int  SocketServer_Client_String_To_CID(char const * const NamBuf)
{
	unsigned int dst_uid;
	
	if(NamBuf == NULL)
	{
		return 0;
	}
	
	dst_uid=SCA_Convert_String_To_UID(NamBuf);
	
	return dst_uid;
}


unsigned long Str2ID(const char* name)
{
	unsigned long s, i;
    for (s = i = 0; name[i]; i++)
		s = (s + (i + 1) * name[i]) % 0x8000000bu * 0xffffffefu;
	return s ^ 0x12345678;
}


union semun { 
   int val;                        /* value for SETVAL */ 
   struct semid_ds *buf;           /* buffer for IPC_STAT, IPC_SET */ 
   unsigned short int *array;      /* array for GETALL, SETALL */ 
   struct seminfo *__buf;          /* buffer for IPC_INFO */ 
}; 




int Open_SSC_Sem(char *Base_Nam)
{
	int          sem_id;
	union semun  sem_union;
	char         ShaMem_Nam_Lock[64]={0};

	if(Base_Nam == NULL)
	{
		return -1;
	}
	
	snprintf(ShaMem_Nam_Lock, sizeof(ShaMem_Nam_Lock), "%s_%s_Lock" ,SHAMEMROY_BASENAME, Base_Nam);

	sem_id=semget(Str2ID(ShaMem_Nam_Lock),1,IPC_CREAT | IPC_EXCL | 0666);
	if(sem_id == -1)
	{
		printf("%s semaphore already exist!\n", ShaMem_Nam_Lock);
		sem_id=semget(Str2ID(ShaMem_Nam_Lock),0,IPC_CREAT | 0666);
		if (sem_id < 0)
		{
			printf("%s sharememory get failed\n", ShaMem_Nam_Lock);
			return -1;
		}
	}
	else
	{
		printf("creat a new %s semaphore!\n", ShaMem_Nam_Lock);
		sem_union.val = 1;  
		if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
		{
			perror("Initialize semaphore failed"); 
			return -1;
		}
	}

	return sem_id;
}



int Del_SSC_sem(int sem_id) 
{
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        perror("Delete semaphore");
        return -1; 
    }
	
	return 0;
}

/* P Sem operation */
int Lock_SSC_Sem(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;          /* one semaphore just use num 0 */
    sem_b.sem_op = -1;          /* indacte the p operation */
    sem_b.sem_flg = SEM_UNDO;   
    if (semop(sem_id, &sem_b, 1) == -1) 
    {
        perror("P operation");
        return -1;
    }
    return 0;
}
	
/* V Sem operation */
int Unlock_SSC_Sem(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;           /* one semaphore just use num 0 */
    sem_b.sem_op = 1;           /* indacte the v operation */
    sem_b.sem_flg = SEM_UNDO;   
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        perror("V operation");
        return -1;
    }
    return 0;
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

	sem_id=Open_SSC_Sem(Base_Nam);
	if(sem_id < 0)
	{
		return -1;
	}

	Lock_SSC_Sem(sem_id);
	
    /*create*/
	fd = shmget(Str2ID(ShaMem_Nam), sizeof(SClnt_NameStore_t), IPC_CREAT | IPC_EXCL | 0666);
	if(-1 == fd)
	{
		printf("%s sharememory already exist!\n", ShaMem_Nam);
		fd = shmget(Str2ID(ShaMem_Nam), sizeof(SClnt_NameStore_t), IPC_CREAT | 0666);
		if (fd < 0)
		{
			printf("%s sharememory get failed\n", ShaMem_Nam);
			Unlock_SSC_Sem(sem_id);
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
		Unlock_SSC_Sem(sem_id);
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

	Unlock_SSC_Sem(sem_id);
	
	return 0;
	
}
