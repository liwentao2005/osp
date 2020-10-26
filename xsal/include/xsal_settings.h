#ifndef XSAL_SETTINGS_H
#   define XSAL_SETTINGS_H
/*===========================================================================*/
/**
 * @file xsal_settings.h
 *
 * XSAL library configuration.
 *
 * %full_filespec:xsal_settings.h~1:incl:ctc_ec#186 %
 * @version %version:1 %
 * @author  %derived_by:fzy8g9 %
 * @date    %date_modified:Wed May  4 16:16:04 2016 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2010 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 *  This has XSAL configuration settings
 *
 * @section ABBR ABBREVIATIONS:
 *   - @todo List any abbreviations, precede each with a dash ('-').
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - @todo Update list of design document(s).
 *
 *   - Requirements Document(s):
 *     - @todo Update list of requirements document(s)
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *     - @todo Update list of other applicable standards
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - @todo List of deviations from standards in this file, or "None".
 *
 * @defgroup xsal_data_types_grp SAL OS Specific data types
 * @{
 */
/*==========================================================================*/

/*===========================================================================*\
 * Header Files
\*===========================================================================*/

#   include "reuse.h"

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/*
 * To statically configure the version of XSAL to build, enable exactly ONE of
 * the following two definitions; otherwise, one of these will have to be
 * defined in the compiler invocation for the build of anything that includes
 * (directly or indirectly) this header file.
 */
#   define XSAL
/*#   define XSAL_LIGHT*/

#   if !defined(XSAL) && !defined(XSAL_LIGHT)
#      error Neither XSAL_LIGHT nor XSAL is defined
#   endif /* !XSAL && !XSAL_LIGHT */

#   if defined(XSAL) && defined(XSAL_LIGHT)
#      error Both macros (XSAL_LIGHT and XSAL) are defined. Only one is allowed.
#   endif /* XSAL && XSAL_LIGHT */

/*
 * The following checks insure that the above selected type of XSAL matches
 * the type of XSAL library specified for the build.
 */
#   if defined(XSAL_LIB)
#      if defined(XSAL_LIGHT)
#         error XSAL library specified for build, but configuration is set to XSAL_LIGHT
#      endif /* if defined(XSAL_LIGHT) */
#   endif /* if defined(XSAL_LIB) */

#   if defined(XSAL_LIGHT_LIB)
#      if defined(XSAL)
#         error XSAL Light library specified for build, but configuration is set to XSAL
#      endif /* if defined(XSAL_LIGHT) */
#   endif /* if defined(XSAL_LIGHT_LIB) */

/*
 * To statically configure the target system, uncomment exactly ONE of the
 * following declarations: LINUX, QNX_NTO, UITRON, or WIN32. If UITRON is
 * declared, then exactly ONE of its variants (UITRON_ESOL or UITRON_RENESAS)
 * must also be declared.
 */
#   if !defined(LINUX)
#      define LINUX    /* Declare this if Linux is the underlying OS */
#   endif

#   if !defined(QNX_NTO)
/*#      define QNX_NTO */ /* Declare this if QNX is the underlying RTOS */
#   endif /* QNX_NTO */

#   if defined(USE_CYGWIN) /* USE_CYGWIN is defined by BASA make system */
#      if !defined(WIN32)
/*#         define WIN32   */ /* Declare this if Windows is the underlying OS */
#      endif
#   endif
/**
 * If uItron is the underlying RTOS, then both UITRON and one of (UITRON_ESOL,
 * UITRON_RENESAS) must be declared.
 */
/*#   define UITRON  */  /* Declare this if uItron is the underlying RTOS */
/*#   define UITRON_ESOL or UITRON_RENESAS*/ /* Pick one if uItron is the RTOS */


/**
 * The following checks make sure that exactly one of the supported RTOSes has
 * been selected.
 */

#   if !defined(LINUX) && !defined(QNX_NTO) && !defined(UITRON) && !defined(WIN32)
#      error Target RTOS not defined
#   endif

#   if defined(LINUX) && (defined(QNX_NTO) || defined(UITRON) || defined(WIN32))
#      error Multiple target RTOSes defined
#   endif

#   if defined(QNX_NTO) && (defined(UITRON) || defined(WIN32))
#      error Multiple target RTOSes defined
#   endif

#   if defined(UITRON) && defined(WIN32)
#      error Multiple target RTOSes defined
#   endif

/**
 * Defines maximum number of timers which application can have.
 *
 * This value may be changed during runtime, calling SAL_Init() function.
 */
#   if !defined(XSAL_MAX_NUMBER_OF_TIMERS)
#      define XSAL_MAX_NUMBER_OF_TIMERS 64
#   endif /* XSAL_MAX_NUMBER_OF_TIMERS */

/**
 * Defines maximum number of Buffer Pools which application can have.
 *
 * This value may be changed during runtime, calling SAL_Init() function.
 */
#   if !defined(XSAL_MAX_NUMBER_OF_BUFFER_POOLS)
#      define XSAL_MAX_NUMBER_OF_BUFFER_POOLS 32
#   endif /* XSAL_MAX_NUMBER_OF_BUFFER_POOLS */

/**
 * Define Sheduling thread polisy (for POSIX systems)
 */
#   if !defined(XSAL_SCHED_POLICY)
#      define XSAL_SCHED_POLICY SCHED_RR
#   endif /* XSAL_SCHED_POLICY */

/** 
 * Maximum length of the thread name (including terminating string byte)
 */
#   define SAL_THREAD_NAME_MAX_LENGTH (20+1)

/**
 * Use thread startup and shutdown synchronization
 */
#   define XSAL_THREAD_STARTUP_SYNCHRONIZATION

/**
 * Use timers
 */
#   define XSAL_TIMERS

/**
 * Linux timers resolution in ms
 */
#   define SAL_I_Timer_Resolution_mS (10u)
/**
 * Timer adjustment to tick period
 *    This accommodates differences between high res clock and system clock.
 *    Nominal is 1000 (uS / mS)
 *    iMX25 is 1024, iMX53 is 1002
 */
#define SAL_I_Timer_Adjust  1024

/**
 * Use Buffer Pools
 */
#   define XSAL_BUFFER_POOLS

/**
 * Use synchronous message passing
 */
#   define XSAL_PUBLISH

/**
 * Default priority for Router Thread
 */
#   if !defined(SAL_ROUTER_THREAD_DEFAULT_PRIORITY)
#      define SAL_ROUTER_THREAD_DEFAULT_PRIORITY SAL_HIGH_PRIORITY
#   endif /* LINUX && SAL_ROUTER_THREAD_DEFAULT_PRIORITY */


#   if defined(QNX_NTO) || defined(LINUX)
#      define XSAL_POSIX
#   endif                       /* QNX_NTO || LINUX */


#   if !defined(XSAL_LIGHT)

/**
 * Use Inter Process Communications
 */
#      define XSAL_IPC
#      define XSAL_EVENT_PROPERTY

/**
 * Use Debug Trace Console
 */
#      define XSAL_DTC

/**
 *  Define multiplier for channels number
 */
#      if !defined(SAL_NS_CHANNEL_MULTIPLIER)
#         define SAL_NS_CHANNEL_MULTIPLIER 3
#      endif /* SAL_NS_CHANNEL_MULTIPLIER */

#   endif /* !XSAL_LIGHT */

/**
 * Define first available application thread
 */
#define XSAL_FIRST_APPLICATION_THREAD_ID  1

/**
 * System default for waiting for XSAL messages
 */
#  ifndef SAL_DEFAULT_MSG_WAIT_TIMEOUT_MS
#     define SAL_DEFAULT_MSG_WAIT_TIMEOUT_MS    (5000)
#  endif

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Const Object Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

/*===========================================================================*/
/*!
 * @file xsal_settings.h
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * - 30-Jun-2011 Theresa Vo Rev 1
 *   - Task 38210: fix SBX using same Synergy objects for cfg files as ICR.
 */
/*==========================================================================*/
/** @} doxygen end group */
#endif /* XSAL_SETTINGS_H */
