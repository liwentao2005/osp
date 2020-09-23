// ----------------------------------------------------------------------------
/**
 * @file    salApplication.h
 *
 * @author  Dariusz Kubiczek
 *
 * @author  2006-2016 Delphi Technologies, Inc., All Rights Reserved
 *          Information Contained Herein Is Proprietary and Confidential
 *
 * @brief   Definition of the Application class.
 */
 // ---------------------------------------------------------------------------

#ifndef XSAL_APPLICATION_H
#define XSAL_APPLICATION_H

#include "salNonCopyable.h"
#include <cstddef>
//#include "xsal.h"

namespace sal
{
   /*class Config;*/

   /**
    *  @class Application
    *  @brief Application class represents the application object.
    *
    *  This base class initializes and runs the application.
    *  An application object must be created and run before any other
    *  XSAL operations.
    *
    *  An example demonstrates how to create and run an application.
   @verbatim

   #include "salApplication.h"

   class MyApp: public sal::Application
   {
   public:
      MyApp( int appId, uint32_t maxNumberOfThreads );

   private:
      // put your variables (e.g., sal::ActiveObjects etc.) and methods here
   };

   MyApp::MyApp( int appId, uint32_t maxNumberOfThreads ):
      sal::Application( appId, maxNumberOfThreads )
   {
      // do your initialization and start your threads here
   }

   int main()
   {
      // main() just starts the application, initializing the application
      // object with the application MY_APP_ID and calling its run() method.

      const int MY_APP_ID = 2;
      const uint32_t MAX_NUMBER_OF_THREADS = 3;

      MyApp myApp( MY_APP_ID, MAX_NUMBER_OF_THREADS );
      return myApp.run();
   }

   @endverbatim
    */
   class Application: private NonCopyable
   {
   public:

      /**
       *  @brief Creates an application object with a given application identifier.
       *
       *  @param [in] appId               the identifier of the application
       *  @param [in] maxNumberOfThreads  maximum number of threads. 
       *                                  the application will have.
       *  @param [in] config              configuration parameters of the 
       *                                  appliation. If 0, the default
       *                                  parameter values are used.
       *
       *  @pre appId > 1, maxNumberOfThreads > 0
       *
       *  @note Application identifier of the value 1 is reserved.
       */
      Application(
         /*SAL_App_Id_T*/int appId,
         int maxNumberOfThreads
         /*const Config* config = 0 */);

      /**
       *  @brief Destroys the application.
       */
      virtual ~Application();

      /**
       *  @brief Runs the application.
       *
       *  @note This method can not be overridden.
       *
       *  @return value of the sal::exitApp() function parameter,
       *    or value 0 when all threads terminate
       */
      int run();
   };

} // namespace sal

#endif // XSAL_APPLICATION_H

/* ----------------------------------------------------------------------------
 * Revision history:
 *
 * 17 September 2020, Wentao Li (liwentao2005@126.com)
 *   Initial revision.
 *
 * --------------------------------------------------------------------------*/
