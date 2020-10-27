/* -------------------------------------------------------------------------
 *
 * File:        xsal_i_version_string.h
 *
 * Copyright:   2006,12 Delphi Technologies, Inc., All Rights Reserved
 *              Information Contained Herein Is Proprietary and Confidential
 *
 * Author:      Jacek Roman (jacek.roman@delphi.com)
 *
 * Description: String with XSAL lib version.
 *
 * %full_filespecdes: %
 * @version %version: 1 %
 * @author  %derived_by: bz08fr %
 * @date    %date_modified: Tue Jun 14 10:45:21 2016 %
 */
/* -------------------------------------------------------------------------*/

#ifndef XSAL_I_VERSION_STRING_H
#define XSAL_I_VERSION_STRING_H

/**
 *  String XSAL_VERSION_STRING defines version of the XSAL lib.
 *  It has the following format:
 *
 *      XSAL XXX YWW Year-Month-Day 
 *
 *  where:
 *
 *   XSAL            lib name
 *   XXX             version number (incremented by 1 on every release)
 *   Y               last digit of the current year
 *   WW              current week number
 *   Year-Month-Day  current date
 *   
 */

#define XSAL_VERSION_STRING "XSAL 2012-12-04"

#endif /* XSAL_I_VERSION_STRING_H */

/* -------------------------------------------------------------------------
 * Revision history:
 *
 * 01 Sep 2006, Jacek Roman (jacek.roman@delphi.com)
 *   Initial revision.
 *
 * -----------------------------------------------------------------------*/
