#ifndef OSP_TIMER_LINUX_H
#   define OSP_TIMER_LINUX_H
/*===========================================================================*/
/**
 * @file xsal_timer_linux.h
 *
 * XSAL Internal Timer functions
 *
 * %full_filespec:xsal_timer_linux.h~1:incl:ctc_ec#30 %
 * @version %version:1 %
 * @author  %derived_by:bz08fr %
 * @date    %date_modified:Tue Jun 14 10:45:22 2016 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2012 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * @todo Add full description here
 *
 * @section ABBR ABBREVIATIONS:
 *   - None
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *
 *   - Requirements Document(s):
 *     - None
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *    - None
 */
/*==========================================================================*/

/*===========================================================================*\
 * Header Files
 \*===========================================================================*/
#include "reuse.h"

/*===========================================================================*\
 * Exported Preprocessor #define Constants
 \*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
 \*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
 \*===========================================================================*/

/**
 * XSAL Timer Status
 */
typedef struct SAL_Timer_Status_Tag
{
   uint16_t num_running; /**< number of active timers waiting to timeout */
   uint16_t num_stopped; /**< number of allocated but stopped timers */
   uint16_t num_unused; /**< number of available unused timers */
} SAL_Timer_Status_T;

/*===========================================================================*\
 * Exported Const Object Declarations
 \*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
 \*===========================================================================*/
/*
 * Access function to get current timer counts
 */
void SAL_Get_Timer_Status(SAL_Timer_Status_T * timer_status);

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
 \*===========================================================================*/

/*===========================================================================*/
/*!
 * @file xsal_timer_linux.h
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * -16-Aug-2011 Dan Carman
 *    - Created initial file.
 */
/*==========================================================================*/
#endif /* XSAL_TIMER_LINUX_H */
