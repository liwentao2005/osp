/* -------------------------------------------------------------------------
 *
 * File:        xsal_destroy_semaphore.c
 *
 * Copyright:   2006 Delphi Technologies, Inc., All Rights Reserved
 *              Information Contained Herein Is Proprietary and Confidential
 *
 * Author:      Jacek Roman (jacek.roman@delphi.com)
 *
 * Description: Implementation of the SAL_Destroy_Semaphore() function.
 *
 * -------------------------------------------------------------------------*/

#include "xsal.h"
#include "xsal_i_assert.h"

#if defined (XSAL_POSIX)

#include <errno.h>
#include <string.h>

#endif /* XSAL_POSIX */

//EM_FILENUM(XSAL_SEM_MODULE_ID, 2); /* Identify file for trace/assert purposes */


/* -----------------------------
 *  Public function definition
 * -----------------------------*/


bool_t SAL_Destroy_Semaphore(SAL_Semaphore_T* sem)
{
#if defined (XSAL_POSIX)

   SAL_Int_T status;

   PBC_Require(sem != NULL, "NULL semaphore");

   status = sem_destroy(sem);
   PBC_Ensure_1((0 == status), "SAL_Destroy_Semaphore error: %s", strerror(errno));

   return (bool_t)(status == 0);

#elif defined (WIN32)

   bool_t status;

   PBC_Require(sem != NULL, "NULL semaphore");

   status = (bool_t)(CloseHandle(*sem) != FALSE);
   PBC_Ensure_1(status, "SAL_Destroy_Semaphore error: %d", (int)GetLastError());

   return status;

#else
#error "Not supported platform"
#endif /* XSAL_POSIX & WIN32 */
}


/* -------------------------------------------------------------------------
 * Revision history:
 *
 * 01 Sep 2006, Jacek Roman (jacek.roman@delphi.com)
 *   Initial revision.
 *
 * -----------------------------------------------------------------------*/
