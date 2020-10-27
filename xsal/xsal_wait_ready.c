/* -------------------------------------------------------------------------
 *
 * File:        xsal_wait_ready.c
 *
 * Copyright:   2006 Delphi Technologies, Inc., All Rights Reserved
 *              Information Contained Herein Is Proprietary and Confidential
 *
 * Author:      Jacek Roman (jacek.roman@delphi.com)
 *
 * Description: Implementation of the SAL_Wait_Ready() function.
 *
 * -----------------------------------------------------------------------*/

#include "xsal.h"
#include "xsal_i_assert.h"
#include "xsal_i_config.h"
#include "xsal_i_thread.h"

//EM_FILENUM(XSAL_THREAD_MODULE_ID, 7); /* Identify file for trace/assert purposes */


/* ----------------------------
 *  Local Function Prototypes
 * ----------------------------*/


/** Function SAL_Wait_Semaphore is not defined in XSAL_LIGHT
 *  external interface but is used internally. 
 */
bool_t SAL_Wait_Semaphore(SAL_Semaphore_T* sem);


/* ------------------------------
 *  Public Function Definitions
 * ------------------------------ */


void SAL_Wait_Ready(
   const SAL_Thread_Id_T thread_id_list[],
   size_t number_of_items)
{
   size_t i;

   for(i = 0; i < number_of_items; i++)
   {
      bool_t status;
      SAL_Thread_Id_T tid = thread_id_list[i];
   
      PBC_Require(tid >= 0, "Negative thread id");
      PBC_Require((size_t)tid <= SAL_I_Max_Number_Of_Threads, "Thread id > max");

      /** 'Decrease' and 'increase' semaphore.
       *  After this operation semaphore will always have 
       *  value 0 or 1 and never exceed the allowable value.
       */
      status = SAL_Wait_Semaphore(&SAL_I_Thread_Table[tid].thread_ready_sem);
      if (status)
      {
         status = SAL_Signal_Semaphore(&SAL_I_Thread_Table[tid].thread_ready_sem);
      }
      PBC_Require(status, "SAL_Wait_Ready failed");
   }
}


/* -------------------------------------------------------------------------
 * Revision history:
 *
 * 01 Sep 2006, Jacek Roman (jacek.roman@delphi.com)
 *   Initial revision.
 *
 * -----------------------------------------------------------------------*/
