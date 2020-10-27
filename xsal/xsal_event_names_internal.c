/*===========================================================================*/
/**
 * @file xsal_event_names.c
 *
 *   Provide names of XSAL events for dbg_trace purposes.
 *
 * %full_filespec:xsal_event_names_internal.c~1:csrc:ctc_ec#9 %
 * @version %version:1 %
 * @author  %derived_by:bz08fr %
 * @date    %date_modified:Tue Jun 14 10:45:27 2016 %
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
 * @section ABBR ABBREVIATIONS:
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *
 *   - Requirements Document(s):
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
#include "xsal.h"

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Exported Const Object Definitions
 *===========================================================================*/

/*===========================================================================*
 * Local Object Definitions
 *===========================================================================*/

#undef  SAL_EVENT
#define SAL_EVENT(id,descr) #id,

/**
 * List of event names.
 */
#ifndef XSAL_DISABLE_EVENT_NAMES
static char_t * SAL_Event_Names[] =
{
   "SAL_EVG_FIRST_PUBLISHED_EVENT_ID",

   //SAL_PUBLISHED_EVENTS

   /** RESERVED for XSAL, must be last published event id; do not change! */
   "SAL_EVG_LAST_PUBLISHED_EVENT_ID",

   //SAL_PUBLIC_EVENTS

   /** First private event identifier value. */
   "SAL_EV_FIRST_PRIVATE_ID",

   //SAL_PRIVATE_EVENTS

   "SAL_LAST_EVENT_ID" /* Must be last - do not move! */
};
#endif

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/

/*
 * Please refer to comment in xsal.h
 */
char_t const *SAL_Get_Event_Name_Xsal(SAL_Event_Id_T event_id)
{
#ifndef XSAL_DISABLE_EVENT_NAMES
   char_t const *name = "ILLEGAL_EVENT";

   if ((event_id > SAL_FIRST_EVENT_ID) && (event_id < SAL_LAST_EVENT_ID))
   {
      name = SAL_Event_Names[event_id];
   }

   return name;
#else
   return "XSAL_EVENT";
#endif
}

/*===========================================================================*/
/*!
 * @file xsal_event_names.c
 *
 * @section RH REVISION HISTORY (top to bottom: first revision to last revision)
 *
 * - 07-May-2012 Kirk Bailey
 *   - Created initial file.
 */
/*===========================================================================*/
