// ----------------------------------------------------------------------------
/**
 * @file    salApplication.cpp
 *
 * @author  Dariusz Kubiczek
 *
 * @author  2006-2016 Delphi Technologies, Inc., All Rights Reserved
 *          Information Contained Herein Is Proprietary and Confidential
 *
 * @brief   Implementation of the Application class.
 */
 // ---------------------------------------------------------------------------

#include "salApplication.h"
#if 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif
//#include "xsal.h"
//#include "salConfig.h"
//#include "pbc_trace.h"
//#include <limits>

namespace sal
{

//////////////////////////////////////////////////////////////////////////////

   Application::Application(
      /*SAL_App_Id_T*/int appId,
      int maxNumberOfThreads/*,
      const Config* config */)
   {
      //PBC_Ensure( appId >= 1, "appId >= 1");
      //PBC_Ensure( maxNumberOfThreads > 0, "masNumberofThreads > 0?" );

      /*SAL_Config_T cfg;
      if ( config )
      {
         cfg = config->mConfig;
      }
      else
      {
         SAL_Get_Config( &cfg );
      }
      cfg.app_id =  appId;
      cfg.max_number_of_threads = maxNumberOfThreads;
      Tr_Info_Hi_1("Created appId %d", appId);
      Tr_Info_Mid_1("Num Threads %u", (unsigned)maxNumberOfThreads);
      (void)SAL_Init( &cfg );*/
   }

//////////////////////////////////////////////////////////////////////////////

   Application::~Application()
   {
   }

//////////////////////////////////////////////////////////////////////////////

   int Application::run()
   {
       while (1) {
           sleep(5);
           printf("sleep well!\n");
       }
      return 0;/*SAL_Run();*/
   }

//////////////////////////////////////////////////////////////////////////////

} // namespace sal

/* ----------------------------------------------------------------------------
 * Revision history:
 *
 * 17 September 2020, Wentao Li (liwentao2005@126.com)
 *   Initial revision.
 *
 * --------------------------------------------------------------------------*/
