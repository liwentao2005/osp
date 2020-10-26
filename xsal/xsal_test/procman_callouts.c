/*===========================================================================*/
/**
 * @file procman_callouts.c
 *
 * This callout file defines xsal attributes for all threads and objects running in the procman process.
 *
 * %full_filespec: procman_callouts.c~1.1.1:csrc:ctc_ec#47 %
 * @version %version: 1.1.1 %
 * @author  %derived_by: wjgprk %
 * @date    %date_modified: Mon May 13 15:07:13 2019 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2011 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * This callout file defines xsal attributes for all threads and objects running in procman.
 * Eventual goal is to place all thread attributes in table 
 *
 * @section ABBR ABBREVIATIONS:
 *   - None
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - None
 *
 *   - Requirements Document(s):
 *     - None
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - None
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include "pbc_trace.h"
#include "procman_cbk.h"
#include "reuse.h"
#include <string.h>
#include "xsal.h"

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
//EM_FILENUM(XSAL_TIME_MODULE_ID, 8); /* Identify file for trace/assert purposes */

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Const Object Definitions
 *===========================================================================*/
 
/**
 * Message Queue Sizes
 */ 
const size_t Timer_Server_Queue_Size = 75;

/*===========================================================================*
 * Local Object Definitions
 *===========================================================================*/

/**
 * Attributes for all predefined SAL threads
 *    name, ID, priority, stack_size, stack_addr (NULL)
 *    Lower priority number, the higher the priority
 */

static const SAL_Thread_Attr_T SAL_Initial_Thread_Attrs[] =
{
   {"SAL thread",      SAL_UNKNOWN_THREAD_ID,  SAL_DEFAULT_THREAD_PRIORITY,    SAL_DEFAULT_THREAD_STACK_SIZE},
   {"Timer Server",    XSAL_TIMER_THREAD_ID,   SAL_VERY_ABOVE_NORMAL_PRIORITY, SAL_DEFAULT_THREAD_STACK_SIZE},
   {"Timer Tick",      TIMER_TICK_THREAD_ID,   SAL_VERY_HIGH_PRIORITY,         SAL_DEFAULT_THREAD_STACK_SIZE},
   {"Name Server",     NAME_SERVER_THREAD,     SAL_DEFAULT_THREAD_PRIORITY,    SAL_DEFAULT_THREAD_STACK_SIZE},
};
                                         
/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/
static void SAL_Get_Initial_Thread_Attr(SAL_Thread_Attr_T * attr, SAL_Thread_Id_T thread_id);

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/

static void SAL_Get_Initial_Thread_Attr(SAL_Thread_Attr_T * attr, SAL_Thread_Id_T thread_id)
{
  volatile unsigned int i;
   
   for (i = Num_Elems(SAL_Initial_Thread_Attrs) - 1; i > 0; i--)
   {
      if (SAL_Initial_Thread_Attrs[i].id == thread_id)
      {
         break;
      }   
   }
   
   (void)memcpy(attr, &SAL_Initial_Thread_Attrs[i], sizeof(SAL_Thread_Attr_T));
   attr->id = thread_id;    /* in case default settings are used, return requested thread id */
}

/*---------------------------------------------------------------------------*
 * XSAL Timer Server (linux only)
 *---------------------------------------------------------------------------*/

/*
 * Please refer to the detailed description in timer_server_cbk.h.
 */
void Timer_Server_Get_Thread_Attr(SAL_Thread_Attr_T * thread_attr)
{
   SAL_Get_Initial_Thread_Attr(thread_attr, XSAL_TIMER_THREAD_ID);
}

/*
 * Please refer to the detailed description in timer_server_cbk.h.
 */
void Timer_Tick_Get_Thread_Attr(SAL_Thread_Attr_T * thread_attr)
{
   SAL_Get_Initial_Thread_Attr(thread_attr, TIMER_TICK_THREAD_ID);
}

/*
 * Notification function Timer_Server is running
 */
void Timer_Server_Initialized(void)
{
}

/*
 * Notification function Timer_Server has shutdown
 */
void Timer_Server_Terminated(void)
{
}

/*---------------------------------------------------------------------------*
 * Procman Threads
 *---------------------------------------------------------------------------*/

void Name_Server_Get_Thread_Attr(SAL_Thread_Attr_T * thread_attr)
{
   SAL_Get_Initial_Thread_Attr(thread_attr, NAME_SERVER_THREAD);
}

void PM_Main_Get_Thread_Attr(SAL_Thread_Attr_T * thread_attr)
{
   SAL_Get_Initial_Thread_Attr(thread_attr, PM_MAIN_THREAD);
}

void PM_Exit_Monitor_Get_Thread_Attr(SAL_Thread_Attr_T * thread_attr)
{
   SAL_Get_Initial_Thread_Attr(thread_attr, PM_EXIT_MONITOR_THREAD);
}

/*===========================================================================*/
/*!
 * @file procman_callouts.c
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * - 02-Jul-2012 Larry Piekarski Rev 3
 *   - Task 106551: Increase size of timer server queue to prevent queue 
 *     overflows on a warm start.
 *
 * - 10-Oct-2011 Dan Carman
 *   - Created initial file.
 *
 *===========================================================================*/
