/*===========================================================================*/
/**
 * @file em_assert.c
 *
 * Handles Asserts thrown by PbC
 *
 * %full_filespec:em_assert.c~4:csrc:ctc_ec#43 %
 * @version %version:4 %
 * @author  %derived_by:fzy8g9 %
 * @date    %date_modified:Fri Nov 10 10:50:55 2017 %
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
 * Implements Assert functionality - depending upon configuration. Configurations can:
 *   - bench - loop in place - useful for debugging with emulator
 *   - ANSI - throw standard assert - useful with cunit test 
 *   - restart - reset and restart software (after logging cause)
 *
 * @section ABBR ABBREVIATIONS:
 *   - PbC Programming by Contract
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
//#include "dbg_trace_cbk.h"
//#include "dbg_trace_cfg.h"
#include "em_assert.h"
//#include "em_cbk.h"

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
 * Performs the actual invocation of the configured EM assert.
 */
void EM_Perform_Assert(void)
{
#if defined(DBG_ENABLE_STACK_BACKTRACE) && (DBG_ENABLE_STACK_BACKTRACE == true)
   Tr_Print_Stack_Backtrace();

   system("/usr/local/bin/soh_dump.sh");
#endif /* DBG_ENABLE_STACK_BACKTRACE == true */

   //EM_Assert();
}


/*===========================================================================*/
/*!
 * @file em_assert.c
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * - 12-Jun-2011 Kirk Bailey Rev. 10
 *   - Eliminated configurable assert types; replaced with a single callout.
 *
 * - 09-Jun-2011 Kirk Bailey Rev. 9
 *   - Call to Tr_Print_Stack_Backtrace() is not made unless backtrace is
 *     enabled.
 *
 * - 03-may-2011 Kris Boultbee
 *   Task kok_basa#30663 Revision 7
 *   - Added call to print out the call stack backtrace upon an assert().
 *
 * - 19-Mar-2010 Dan Carman
 *   - Remove unused EM_Lock / Unlock macros and therrefore include of interrupts
 *
 * - 14-sep-2009 kirk bailey
 *   - Task kok_aud 56926: Removed EM_STANDALONE (use TR_STAND_ALONE)
 *
 * - 10-feb-2009 kirk bailey
 *   - Moved declarations of assert mode constants in front of their reference
 *     in conditional compilation to fix an SH2A compiler warning.
 *
 * - 23-Dec-2008 Dan Carman
 *   - Created initial file.
 */
/*===========================================================================*/
