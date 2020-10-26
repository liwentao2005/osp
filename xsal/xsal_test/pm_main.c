/*--------------------------------------------------------------------------
 * File:           main.c
 *
 * Copyright:      2004 Delphi Technologies, Inc., All Rights Reserved
 *                 Information Contained Herein Is Proprietary and Confidential
 *
 * Author          Michal Gebolys / Lukasz Ptak
 *
 * Description:    The ProcessManager application.
 *
 *--------------------------------------------------------------------------
 */
#include <stdio.h>
#include <signal.h>
#include <string.h>

#include "xsal.h"
#include "pi_stdlib.h"
#include "xsal_ns_thread.h"
#include "pbc_trace.h"
#include "dbg_trace.h"
//#include "pm_process.h"
//#include "pm_main_thread.h"
//#include "pm_exit_monitor.h"
#include "procman_cbk.h"
//#include "privilege_mgr_api.h"
//#include "privilege_mgr_acfg.h"

static void Int_Signal_Handler(int sig_no)
{
   signal(SIGINT, SIG_DFL);
#if 0
   if (!SAL_Is_Thread_Alive(PM_MAIN_THREAD))
   {
      /* Only Name Server thread is running
       * It's not allowed to use any XSAL functions 
       * in asynchronous signal handler function e.g. SAL_Exit( 0 );
       */
      SAL_Name_Server_Destroy();
      SAL_Destroy_Channel(&SAL_I_RT_Channel);
      _exit(0);
   }
   PM_Stop_Main_Thread();
   #endif
}

static void Start_Threads(void)
{
   SAL_Thread_Attr_T thread_attr;
   SAL_Thread_Id_T   ok;

   Name_Server_Get_Thread_Attr(&thread_attr);

   if (SAL_Start_Name_Server_Thread(&thread_attr) < 0)
   {
      //Tr_Fault("Couldn't start Name Server thread");
      exit(1);
   }
#if 0
   if (init_values.f == 1 && PM_Parse_Config_File(init_values.file_name))
   {
      PM_Main_Get_Thread_Attr(&thread_attr);
      ok = SAL_Create_Thread(PM_Main_Thread, NULL, &thread_attr);
      PBC_Ensure(ok, "SAL_Create_Thread: PM_Main_Thread error");

#if defined(XSAL_POSIX)

      PM_Exit_Monitor_Get_Thread_Attr(&thread_attr);
      ok = SAL_Create_Thread(PM_Exit_Monitor_Thread, NULL, &thread_attr);
      PBC_Ensure(ok, "SAL_Create_Thread: PM_Exit_Monitor_Thread error");

#endif /* XSAL_POSIX */

   }
   #endif
}

static void Sigpipe_Handler(int signal_id, siginfo_t *info, void *context)
{
   //Tr_Warn("SIGPIPE handled");
}

int main(int argc, char* argv[])
{
    int ret = 0;
    int status;
    const char *name;
    struct sigaction sigpipe_action = { { 0 } };

    sigpipe_action.sa_flags = SA_SIGINFO;
    sigpipe_action.sa_sigaction = Sigpipe_Handler;
    if (0 != sigaction(SIGPIPE, &sigpipe_action, NULL))
    {
        //Tr_Fault("sigaction() failed for SIGPIPE");
    }
   
    //PM_Print_Performance_Info("Procman started", 0);

    //status = Parse_Command_Line(argc, argv);

    if (SAL_Name_Server_Init())
    {
        SAL_Config_T config;
        SAL_Get_Config(&config);

        /* install signal handler */
        signal(SIGINT, &Int_Signal_Handler);

        config.app_id = APP_PROCMAN;
        config.max_number_of_threads = PM_LAST_THREAD_ID;
        if (!SAL_Init(&config))
        {
            //Tr_Fault_1("SAL_Init status = %d", (int)1);
            exit(1);
        }

        Start_Threads();
        ret = SAL_Run();
        SAL_Name_Server_Destroy();
    }
    else
    {
        ret = 1;
    }

    return ret;
}
