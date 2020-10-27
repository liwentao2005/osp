#ifndef UTILITIES_H
#   define UTILITIES_H
/*===========================================================================*/
/**
 * @file utilities.h
 *
 * Collection of general purpose utility routine API's
 *
 * %full_filespec:utilities.h~1.2.1:incl:ctc_ec#90 %
 * @version %version:1.2.1 %
 * @author  %derived_by:qjj06p %
 * @date    %date_modified:Thu Sep 14 20:31:29 2017 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2007 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * Collection of general purpose utility routines
 *
 * @section ABBR ABBREVIATIONS:
 *   - None
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - SDD_BASA_Utilities.doc
 *
 *   - Requirements Document(s):
 *     - SRS_BASA_Utilities.doc
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DEV DEVIATIONS FROM STANDARDS:
 *   - None
 *
 * @mainpage
 * @section intro Introduction
 *
 * The utilities module is a collection of files that implement commonly used
 * functions. Each file is stand alone and requires no configuration or special
 * setup.
 *
 * @note WARNING: None of these functions are thread safe. In an effort to make 
 * these functions as generic as possible, specific OS dependencies are not included. 
 * It is the users responsibility to understand what "Thread Safe" means, if it applies
 * in their specific case, and to take appropriate project specific actions
 * to provide thread safeness in their particular instance.
 *
 * @ref bdb_lite_page
 *
 * @ref bit_array_page
 *
 * @ref checksum_page
 *
 * @ref conversion_page
 *
 * @ref convert_endian_page
 *
 * @ref double_linked_list_page
 *
 * @ref hex_string_page
 *
 * @ref interpolation_page
 *
 * @ref limit_check_page
 *
 * @ref low_pass_filter_page
 *
 * @ref ring_buffer_page
 *
 * @ref string_util_page
 *
 * @defgroup utilities_grp General Purpose Utility Routines
 * @{
 */
/*==========================================================================*/

/*===========================================================================*\
 * Header Files
\*===========================================================================*/ 
//#   include "bdb_lite.h"
//#   include "bit_array.h"
//#   include "checksum.h"
//#   include "conversions.h"
//#   include "convert_8859_1_to_utf8.h"
//#   include "convert_endian.h"
//#   include "double_linked_list.h"
//#   include "hex_string.h"
//#   include "interpolate.h"
//#   include "limit_check.h"
//#   include "low_pass_filter.h"
//#   include "ring_buffer.h"
#   include "string_res.h"


/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/
/**
 * Can be used to silence warnings about unused arguments or variables.
 */
#   ifndef UNUSED_PARAM
#      define UNUSED_PARAM(argument) (void)(argument)
#   endif

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Const Object Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/
#   ifdef __cplusplus
extern "C" 
{
   
#   endif                       /* __cplusplus */

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

#   ifdef __cplusplus
} 
#   endif /* __cplusplus */
/*===========================================================================*/
/*!
 * @file utilities.h
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * - 12-Apr-2012 Jim Huemann Revision 11
 *   - Added Convert_8859_1_to_UTF8
 *
 * - 21-apr-2010 Kirk Bailey Rev 10
 *   - Eliminated extern C block (no function prototypes).
 *
 * - 05-Jun-2009 Larry Piekarski Rev 8
 *   - Added note from peer review that these functions are not thread safe.
 *
 * - 27-May-2009 Larry Piekarski Rev 7
 *   - Cleaned up code from review checklist
 *
 * - 15-May-2009 Larry Piekarski Rev 6
 *   - Added bdb_lite.h
 *   - Updated Doxygen Comments
 *
 * - 14-feb-2008 kirk bailey
 *   - Renamed dbl_ll to double_linked_list.
 *
 * - 10-jan-2008 kirk bailey
 *   - Added double linked list support (dbl_ll) to utilities.
 *
 * - 14-Jun-2007 Bartosz Jamrozik
 *   - added include files:
 *     checksum.h, string_res.h
 *
 * - 22-May-2007 Bartosz Jamrozik
 *   - added includes header files
 *
 * - 02-feb-2007 Dan Carman
 *   - Created initial file.
 *
\*===========================================================================*/
/** @} doxygen end group */
#endif                          /* UTILITIES_H */
