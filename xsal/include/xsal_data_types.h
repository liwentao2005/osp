#ifndef XSAL_DATA_TYPES_H
#   define XSAL_DATA_TYPES_H
/*===========================================================================*/
/**
 * @file xsal_data_types.h
 *
 * Defines basic XSAL data types.
 *
 * %full_filespec:xsal_data_types.h~1:incl:ctc_ec#67 %
 * @version %version:1 %
 * @author  %derived_by:bz08fr %
 * @date    %date_modified:Tue Jun 14 10:45:13 2016 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2007 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * DESCRIPTION:
 *
 *  This has XSAL data type declarations.
 *
 * ABBREVIATIONS:
 *   - XSAL = eXtended System Abstraction Layer
 *
 * TRACEABILITY INFO:
 *   - Design Document(s):
 *     - XSAL_API.doc March 1, 2007.
 *
 *   - Requirements Document(s):
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *    - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * DEVIATIONS FROM STANDARDS:
 *   - None
 *
 * @defgroup xsal_data_types_grp SAL OS Specific data types
 * @{
 */
/*==========================================================================*/

#   ifdef __cplusplus
extern "C"
{
#   endif /* __cplusplus */

/*===========================================================================*\
 * Header Files
\*===========================================================================*/

#   include "reuse.h"
#   include "xsal_settings.h"

/** 
 * SAL_Int_T type is used internally as procesor native word.
 * On N-bit platforms it should be defined as intN_t.
 */
typedef int32_t SAL_Int_T;

/**
 * SAL_App_Id_T defines the storage for application (process) ids.
 */
typedef uint8_t SAL_App_Id_T;

typedef SAL_Int_T  SAL_Sched_Policy_T;

/**
 * SAL_Buffer_Pool_Id_T defines the type used to identify buffer pools.
 */
#   if !defined(XSAL_LIGHT)
typedef SAL_Int_T SAL_Port_Id_T;
#   endif

/**
 * SAL_Shared_Memory_Key_T defines the type used to identify shared memory keys.
 */
#   if !defined(XSAL_LIGHT)
typedef SAL_Int_T SAL_Shared_Memory_Key_T;
#   endif

#   if defined (QNX_NTO)

#      include "xsal_data_types_qnx.h"

#   elif defined (LINUX)

#      include "xsal_data_types_linux.h"

#   elif defined (WIN32)

#      include "xsal_data_types_win32.h"


#   elif defined (UITRON)

#      include "xsal_data_types_uitron.h"

#   else
#      error "Not supported platform"
#   endif


#   include "xsal_thread_priority.h"

/* -------------------------------------------------------------------------
 *
 *                           Shared memory management
 *
 * -----------------------------------------------------------------------*/


/** 
 *  Open mode of the shared memory area
 */
typedef enum SAL_Shared_Memory_Open_Mode_Tag
{
   /** Open shared memory in read-write mode
    */
   SAL_SHMEM_RDWR   = 0, 

   /** Open shared memory in read-only mode
    */
   SAL_SHMEM_RDONLY = 1
} SAL_Shared_Memory_Open_Mode_T;
 

/* -------------------------------------------------------------------------
 *
 *                           Name Server
 *
 * -----------------------------------------------------------------------*/

/** Size allocated for an XSAL application name from the name server. */
#define SAL_MAX_APP_NAME 64
/** Size allocated for a debug module name from the name server. */
#define SAL_MAX_DBG_MODULE_NAME 64

/**
 * XSAL Application data available from the name server.
 */
typedef struct SAL_App_Data_Tag
{
	uint16_t app_id;       /**< XSAL application id */
	bool_t   is_running;   /**< True if app is running */
	char     app_name[SAL_MAX_APP_NAME]; /**< Name of XSAL application */
}
SAL_App_Data_T;

/**
 * Debug module data available from the name server.
 */
typedef struct SAL_Dbg_Module_Data_Tag
{
	uint16_t module_id;  /**< Debug module id value */
	char     module_name[SAL_MAX_DBG_MODULE_NAME]; /**< Name of debug module */
}
SAL_Dbg_Module_Data_T;


/* -------------------------------------------------------------------------
 *
 *                           Thread management
 *
 * -----------------------------------------------------------------------*/


/** 
 *  Thread ID of the Router Thread
 */
#define SAL_ROUTER_THREAD_ID 0
#define SAL_UNKNOWN_THREAD_ID (-1)


/** 
 *  Command ID's for Router Thread
 */
enum SAL_RT_Event_T
{
   EV_RT_DT_Command   = -1,
   EV_RT_Last_Command = -2
};

/***********************************
 *
 *       Timer configuration
 *
 ***********************************/

/** There are 3 SAL Timer implementations for diffrent OS's:
 *
 *  PULSES    - this should be selected for QNX
 *  SIGNALS   - this should be selected for UNIX/LINUX or QNX
 *  WIN32_API - this should be selected for Windows
 */
#define XSAL_TIMER_USE_PULSES    1
#define XSAL_TIMER_USE_SIGNALS   2
#define XSAL_TIMER_USE_WIN32_API 3


/** Choose SAL Timer implementation.
 *
 *  User must change this macro, depending on their operating system.
 */
#if !defined(XSAL_TIMER_IMPL)
#if defined(QNX_NTO)
#define XSAL_TIMER_IMPL XSAL_TIMER_USE_PULSES
#elif defined(WIN32)
#define XSAL_TIMER_IMPL XSAL_TIMER_USE_WIN32_API
#else
#define XSAL_TIMER_IMPL XSAL_TIMER_USE_SIGNALS
#endif /* QNX_NTO && WIN32 */
#endif /* XSAL_TIMER_IMPL */

#   ifdef __cplusplus
}
#   endif /* __cplusplus */
/*===========================================================================*\
 * File Revision History (top to bottom: laast revision to first revision)
 *===========================================================================
 *
 * Date        Name      (Description on following lines: SCR #, etc.)
 * ----------- --------
 * 24-Jan-2011 kirk bailey
 * + Added new app/debug module types for name server.
 *
 * 27-mar-2008 kirk bailey
 * + Returned to DB48x approach of separate files. Merged uItron defns.
 *
\*===========================================================================*/
/** @} doxygen end group */
#endif /* XSAL_DATA_TYPES_H */
