#include <stdio.h>
#include "MyLog.h"
#if 1

#define TR_FILE_ID EM_F_ID
#define TR_LVL_FAULT 0
#define SAL_Check_Return_Status_OK(status, command)   SAL_Check_Return_Status_OK_Function(status, command, TR_FILE_ID, __FILE__, __LINE__)
#define _FILE_OFFSET_BITS 64
#define FBL_MGR_MODULE_ID 1
#define UTILITIES_MODULE_ID 2
#define EM_MOD_SHIFT_CNT 4
#define EM_FILE_ID(mod_id, fidx) (((mod_id) << EM_MOD_SHIFT_CNT) + ((fidx)&(0xffff>>(16-EM_MOD_SHIFT_CNT))))
#define EM_FILENUM(mod_id, fidx) enum{EM_F_ID = EM_FILE_ID(mod_id, fidx)}
#define SAL_Alloc malloc
#define SAL_Free free
//#define PBC_Require(expr_,msg_) ((void)0)
//#define PBC_Internal(expr_,msg_) ((void)0)
//#define PBC_Failed_1(msg_,a1_) ((void)0)
//#define PBC_Require_1(expr_,msg_,a1_) ((void)0)
#if 1
//Error
#define Tr_Fault(msg)					printf("Fault: "msg"\n")
#define Tr_Fault_1(msg,a1)              printf("Fault: "msg"\n",a1)
#define Tr_Fault_2(msg,a1,a2)           printf("Fault: "msg"\n",a1,a2)
#define Tr_Fault_3(msg,a1,a2,a3)        printf("Fault: "msg"\n",a1,a2,a3)
#define Tr_Fault_4(msg,a1,a2,a3,a4)     printf("Fault: "msg"\n",a1,a2,a3,a4)
//Warning
#define Tr_Warn(msg)					printf("Warn: "msg"\n")
#define Tr_Warn_1(msg,a1)               printf("Warn: "msg"\n",a1)
#define Tr_Warn_2(msg,a1,a2)            printf("Warn: "msg"\n",a1,a2)
#define Tr_Warn_3(msg,a1,a2,a3)         printf("Warn: "msg"\n",a1,a2,a3)
#define Tr_Warn_4(msg,a1,a2,a3,a4)      printf("Warn: "msg"\n",a1,a2,a3,a4)
//Info
#define Tr_Notify(msg)					printf("Notify: "msg"\n")
#define Tr_Notify_1(msg,a1)				printf("Notify: "msg"\n",a1)
#define Tr_Notify_2(msg,a1,a2)			printf("Notify: "msg"\n",a1,a2)
#define Tr_Notify_3(msg,a1,a2,a3)		printf("Notify: "msg"\n",a1,a2,a3)
#define Tr_Notify_4(msg,a1,a2,a3,a4)	printf("Notify: "msg"\n",a1,a2,a3,a4)
//debug_H
#define Tr_Info_Hi(msg)					printf("INFO_Hi: "msg"\n")
#define Tr_Info_Hi_1(msg,a1)            printf("INFO_Hi: "msg"\n",a1)
#define Tr_Info_Hi_2(msg,a1,a2)         printf("INFO_Hi: "msg"\n",a1,a2)
#define Tr_Info_Hi_3(msg,a1,a2,a3)      printf("INFO_Hi: "msg"\n",a1,a2,a3)
#define Tr_Info_Hi_4(msg,a1,a2,a3,a4)   printf("INFO_Hi: "msg"\n",a1,a2,a3,a4)
//debug_M
#define Tr_Info_Mid(msg)				printf("INFO_Mid: "msg"\n"fhfh)
#define Tr_Info_Mid_1(msg,a1)           printf("INFO_Mid: "msg"\n",a1)
#define Tr_Info_Mid_2(msg,a1,a2)        printf("INFO_Mid: "msg"\n",a1,a2)
#define Tr_Info_Mid_3(msg,a1,a2,a3)     printf("INFO_Mid: "msg"\n",a1,a2,a3)
#define Tr_Info_Mid_4(msg,a1,a2,a3,a4)  printf("INFO_Mid: "msg"\n",a1,a2,a3,a4)
//debug_L
#define Tr_Info_Lo(msg)					printf("INFO_Lo: "msg"\n")
#define Tr_Info_Lo_1(msg,a1)            printf("INFO_Lo: "msg"\n",a1)
#define Tr_Info_Lo_2(msg,a1,a2)         printf("INFO_Lo: "msg"\n",a1,a2)
#define Tr_Info_Lo_3(msg,a1,a2,a3)      printf("INFO_Lo: "msg"\n",a1,a2,a3)
#define Tr_Info_Lo_4(msg,a1,a2,a3,a4)   printf("INFO_Lo: "msg"\n",a1,a2,a3,a4)
#else
//Error
#define Tr_Fault(msg)					Log(ERROR, msg"\n")
#define Tr_Fault_1(msg,a1)              Log(ERROR, msg"\n",a1)
#define Tr_Fault_2(msg,a1,a2)           Log(ERROR, msg"\n",a1,a2)
#define Tr_Fault_3(msg,a1,a2,a3)        Log(ERROR, msg"\n",a1,a2,a3)
#define Tr_Fault_4(msg,a1,a2,a3,a4)     Log(ERROR, msg"\n",a1,a2,a3,a4)
//Warning
#define Tr_Warn(msg)					Log(WARNING, msg"\n")
#define Tr_Warn_1(msg,a1)               Log(WARNING, msg"\n",a1)
#define Tr_Warn_2(msg,a1,a2)            Log(WARNING, msg"\n",a1,a2)
#define Tr_Warn_3(msg,a1,a2,a3)         Log(WARNING, msg"\n",a1,a2,a3)
#define Tr_Warn_4(msg,a1,a2,a3,a4)      Log(WARNING, msg"\n",a1,a2,a3,a4)
//Info
#define Tr_Notify(msg)					Log(INFO, msg"\n")
#define Tr_Notify_1(msg,a1)				Log(INFO, msg"\n",a1)
#define Tr_Notify_2(msg,a1,a2)			Log(INFO, msg"\n",a1,a2)
#define Tr_Notify_3(msg,a1,a2,a3)		Log(INFO, msg"\n",a1,a2,a3)
#define Tr_Notify_4(msg,a1,a2,a3,a4)	Log(INFO, msg"\n",a1,a2,a3,a4)
//debug_H
#define Tr_Info_Hi(msg)					Log(DEBUG, msg"\n")
#define Tr_Info_Hi_1(msg,a1)            Log(DEBUG, msg"\n",a1)
#define Tr_Info_Hi_2(msg,a1,a2)         Log(DEBUG, msg"\n",a1,a2)
#define Tr_Info_Hi_3(msg,a1,a2,a3)      Log(DEBUG, msg"\n",a1,a2,a3)
#define Tr_Info_Hi_4(msg,a1,a2,a3,a4)   Log(DEBUG, msg"\n",a1,a2,a3,a4)
//debug_M
#define Tr_Info_Mid(msg)				Log(DEFAULT, msg"\n"fhfdhfdh)
#define Tr_Info_Mid_1(msg,a1)           Log(DEFAULT, msg"\n",a1)
#define Tr_Info_Mid_2(msg,a1,a2)        Log(DEFAULT, msg"\n",a1,a2)
#define Tr_Info_Mid_3(msg,a1,a2,a3)     Log(DEFAULT, msg"\n",a1,a2,a3)
#define Tr_Info_Mid_4(msg,a1,a2,a3,a4)  Log(DEFAULT, msg"\n",a1,a2,a3,a4)
//debug_L
#define Tr_Info_Lo(msg)					Log(DEFAULT, msg"\n")
#define Tr_Info_Lo_1(msg,a1)            Log(DEFAULT, msg"\n",a1)
#define Tr_Info_Lo_2(msg,a1,a2)         Log(DEFAULT, msg"\n",a1,a2)
#define Tr_Info_Lo_3(msg,a1,a2,a3)      Log(DEFAULT, msg"\n",a1,a2,a3)
#define Tr_Info_Lo_4(msg,a1,a2,a3,a4)   Log(DEFAULT, msg"\n",a1,a2,a3,a4)

#endif
#endif
