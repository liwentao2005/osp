/*===========================================================================*/
/**
 * @file string_res.c
 *
 * Functions to support string handling
 *
 * %full_filespec:string_res.c~2:csrc:ctc_ec#41 %
 * @version %version:2 %
 * @author  %derived_by:kz0wz6 %
 * @date    %date_modified:Thu Aug 25 14:04:08 2016 %
 *
 *------------------------------------------------------------------------------
 *
 * Copyright 2007-2012 Delphi Technologies, Inc., All Rights Reserved.
 * Delphi Confidential
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * Functions to support string handling
 *
 * @section ABBR ABBREVIATIONS:
 *
 * @section TRA TRACEABILITY INFO:
 *   - Design Document(s):
 *     - SDD_BASA_Utilities
 *
 *   - Requirements Document(s):
 *     - SRS_BASA_Utilities
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - <a href="http://kogespw1.delcoelect.com:8508/passthru/consumer?name=SW%20REF%20264.15D&doctype=K8DBSDoc">
 *       SW REF 264.15D "Delphi C Coding Standards" [12-Mar-2006]</a>
 *
 * @section DFS DEVIATIONS FROM STANDARDS:
 *   - None.
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/

#define DISABLE_DEPRECATED_STRCPY  /* Allow strcpy usage in this file  */
#define DISABLE_DEPRECATED_STRNCPY /* Allow strncpy usage in this file */

#include <ctype.h>
#include "pbc_trace.h"
#include <stdlib.h>
#include <string.h>
#include "string_res.h"

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/
EM_FILENUM(UTILITIES_MODULE_ID, 11); /**< IDs file for EM assert handling */

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
static const char_t *copy_display_string(char_t * dest, const char_t * buf, int16_t num_chars);
static const char_t *start_of_next_word(const char_t * buf, bool_t(*str_char_is_blank)(const char_t char_to_test));
static int16_t length_next_word(const char_t * buf, int16_t max_allowable, bool_t(*str_char_is_blank)(
   const char_t char_to_test));
/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/
/**
 * Copy string
 *
 * @return pointer to past end of word in input string
 *
 * @param [in] dest pointer to a string
 * @param [in] buf pointer to large string
 * @param [in] num_chars pointer to a string
 */
static const char_t *copy_display_string(char_t * dest, const char_t * buf, int16_t num_chars)
{
   PBC_Require((dest != NULL) && (buf != NULL), "copy_display_string called with NULL pointer");

   while ((*buf != '\0') && (num_chars > 0))
   {
      *dest = *buf;
      dest++;
      buf++;
      num_chars--;
   }
   return (buf);
}

/**
 * Advance pointer past white space
 *
 * @return Pointer to start of text or end of the string
 *
 * @param [in] buf pointer to a string
 * @param [in] str_char_is_blank pointer to callback function. The function shall return true
 *             if given character is visible on display
 */
static const char_t *start_of_next_word(const char_t * buf, bool_t(*str_char_is_blank)(const char_t char_to_test))
{
   PBC_Require((buf != NULL) && (str_char_is_blank != NULL), "start_of_next_word called with NULL pointer");

   while ((*buf != '\0') && (str_char_is_blank(*buf)))
   {
      buf++;
   }
   return (buf);
}

/**
 * Determines the length of the next word in a string
 *
 * @return Number of characters <= max size of next word in string
 *
 * @param [in] buf pointer to a string
 * @param [in] max_allowable largest possible word size
 * @param [in] str_char_is_blank pointer to callback function. The function shall return true
 *             if given character is visible on display
 */
static int16_t length_next_word(const char_t * buf, int16_t max_allowable, bool_t(*str_char_is_blank)(
   const char_t char_to_test))
{
   int16_t char_count = 0;

   PBC_Require((buf != NULL) && (str_char_is_blank != NULL), "length_next_word called with NULL pointer");

   while ((!str_char_is_blank(*buf)) && (char_count < max_allowable))
   {
      buf++;
      char_count++;
   }

   return (char_count);
}

/*
 * Please refer to description in string_res.h
 */
size_t Safe_Strlen(char const *s, size_t max_size)
{
   size_t sz = 0;

   PBC_Require(s != NULL, "NULL C string pointer");
   if (s != NULL)
   {
      while ((sz < max_size) && (s[sz] != '\0'))
      {
         sz++;
      }
   }

   return sz;
}

/*
 * Please refer to description in string_res.h
 */
char* Safe_Strncat(char* dest, char const* src, size_t dest_size)
{
   return Str_Full_Concat(dest, src, dest_size);
}

/**
 * Appends "src" string to "dest" making sure that the destination buffer is
 * not overflowed and that the result is NUL terminated.
 *
 * @param dest Pointer to beginning of destination buffer
 * @param dest_length Length of current contents; src is copied starting here.
 * @param dest_size Total size of dest buffer which cannot be exceeded.
 * @param src Pointer to src data to be copied.
 * @param src_length Number of bytes to be copied from the src
 */
static void Str_Append(char* dest, size_t dest_length, size_t dest_size, char const *src, size_t src_length)
{
   size_t num_to_copy;

   PBC_Internal(dest_length <= dest_size, "Length of buffer contents larger than buffer size");

   if (dest_length + src_length >= dest_size)
   { /*
    * Some truncation of src will occur.
    */
      num_to_copy = dest_size - dest_length;
   }
   else
   { /*
    * All of src plus a NUL terminator will fit. Only src_length+1
    * bytes are copied to avoid extra overhead from filling a large
    * number of trailing bytes with zero - only a single NUL terminator
    * is required.
    */
      num_to_copy = src_length + 1;
   }
   Safe_Strncpy(dest + dest_length, src, num_to_copy);
}

/*
 * Please refer to description in string_res.h
 */
char* Safe_Strncpy(char* dest, char const* src, size_t dest_size)
{
   return Str_Full_Copy(dest, src, dest_size);
}

/*
 * Please refer to description in string_res.h
 */
char* Str_Full_Concat(char* dest, char const* src, size_t dest_size)
{
   PBC_Require(dest != NULL, "NULL destination string pointer");
   PBC_Require(src != NULL, "NULL source string pointer");
   if ((dest != NULL) && (src != NULL) && (dest_size > 0))
   {
      size_t dest_length = Safe_Strlen(dest, dest_size);

      if (dest_length >= dest_size)
      { /*
       * Initial contents of dest are already too long to fit more
       * characters plus a NUL terminator. Here we make sure there is
       * a NUL terminator at the designated end of the buffer.
       */
         dest[dest_size - 1] = '\0';
      }
      else
      {
         size_t src_length = strlen(src); /* no "safer" way since no other data about src */
         Str_Append(dest, dest_length, dest_size, src, src_length);
      }
   } /* if ((dest != NULL) && (src != NULL) && (dest_size > 0)) */

   return dest;
}

/*
 * Please refer to description in string_res.h
 */
char* Str_Full_Copy(char* dest, char const* src, size_t dest_size)
{
   PBC_Require(dest != NULL, "NULL destination string pointer");
   PBC_Require(src != NULL, "NULL source string pointer");
   if ((dest != NULL) && (src != NULL) && (dest_size > 0))
   {
      size_t src_length = Safe_Strlen(src, dest_size);
      size_t num_to_copy;

      if (dest_size > src_length)
      {
         num_to_copy = src_length;
      }
      else
      {
         num_to_copy = dest_size - 1; /* Leave room for NUL terminator */
      }
      strncpy(dest, src, num_to_copy);
      dest[num_to_copy] = '\0';
   }
   return dest;
}

/**
 * Copy a portion (broken on word boundary) of a large string into a smaller string
 */
char_t *Str_Get_Sub_String(char_t * dest_str, const char_t * src_str, int16_t size, bool_t break_on_word,
   bool_t(*str_char_is_blank)(const char_t char_to_test))
{
   int16_t length;
   int16_t remaining_buf_len = size;
   char_t *dest = dest_str;

   PBC_Require((dest_str != NULL) && (src_str != NULL) && (str_char_is_blank != NULL), "Str_Get_Sub_String called with NULL pointer");

   if (!break_on_word)
   {
      src_str = copy_display_string(dest_str, src_str, size);
   }
   else
   {
      src_str = start_of_next_word(src_str, str_char_is_blank);
      length = length_next_word(src_str, size, str_char_is_blank);

      while ((0 != length) && (length <= remaining_buf_len))
      {
         src_str = copy_display_string(dest, src_str, length);
         remaining_buf_len -= length;
         dest += length;

         if ((remaining_buf_len > 0) && (str_char_is_blank(*src_str)))
         {
            *dest++ = ' ';
            remaining_buf_len--;
         }
         src_str = start_of_next_word(src_str, str_char_is_blank);
         length = length_next_word(src_str, size, str_char_is_blank);
      }
      if ((str_char_is_blank(*(dest - 1))) && (remaining_buf_len != size))
      {
         dest--;
      }

   }

   *dest = '\0';
   return ((char_t *) src_str);
}

/*
 * Determines if the string will be visible
 */
bool_t Str_Is_Blank_String(const char_t * buf, bool_t(*str_char_is_blank)(const char_t char_to_test))
{
   bool_t blank = true;

   PBC_Require((buf != NULL) && (str_char_is_blank != NULL), "Str_Is_Blank_String called with NULL pointer");

   if ((NULL != buf) || (NULL != str_char_is_blank)) /* always return true for null strings */
   {
      buf = start_of_next_word(buf, str_char_is_blank);
      blank = ('\0' == *buf); /* if at end of string then blank */
   }

   return blank;
}

/*
 * Please refer to description in string_res.h
 */
bool_t Str_Is_Empty(const char *str)
{
   bool_t result = true;

   PBC_Require(str != NULL, "NULL string pointer");

   if (str != NULL)
   {
      result = (str[0] == '\0');
   }
   return result;
}

/*
 * Please refer to description in string_res.h
 */
char* Str_Partial_Concat(char* dest, char const* src, size_t max_chars_from_src, size_t dest_size)
{
   PBC_Require(dest != NULL, "NULL destination string pointer");
   PBC_Require(src != NULL, "NULL source string pointer");
   if ((dest != NULL) && (src != NULL) && (dest_size > 0))
   {
      size_t dest_length = Safe_Strlen(dest, dest_size);

      if (dest_length >= dest_size)
      { /*
       * Initial contents of dest are already too long to fit more
       * characters plus a NUL terminator. Here we make sure there is
       * a NUL terminator at the designated end of the buffer.
       */
         dest[dest_size - 1] = '\0';
      }
      else
      {
         size_t src_length = Safe_Strlen(src, max_chars_from_src);
         Str_Append(dest, dest_length, dest_size, src, src_length);
      }
   } /* if ((dest != NULL) && (src != NULL) && (dest_size > 0)) */

   return dest;
}

/*
 * Please refer to description in string_res.h
 */
char* Str_Partial_Copy(char* dest, char const* src, size_t max_chars_from_src, size_t dest_size)
{
   PBC_Require(dest != NULL, "NULL destination string pointer");
   PBC_Require(src != NULL, "NULL source string pointer");
   if ((dest != NULL) && (src != NULL) && (dest_size > 0))
   {
      size_t num_to_copy;

      if (dest_size > max_chars_from_src)
      {
         num_to_copy = max_chars_from_src;
      }
      else
      {
         num_to_copy = dest_size - 1; /* Leave room for NUL terminator */
      }
      strncpy(dest, src, num_to_copy);
      dest[num_to_copy] = '\0';       /* Guarantee NUL terminator */
   }
   return dest;
}

/**
 * Exchanges n bytes between an object indicated by src1 and an object indicated by src2
 */
void memexch(void *src1, void *src2, size_t n)
{
   char_t *pch1;
   char_t *pch2;
   char_t temp;

   PBC_Require((src1 != NULL) && (src2 != NULL), "memexch called with NULL pointer");

   if (src1 < src2) /* set lower address to ch1 */
   {
      pch1 = (char_t *) src1;
      pch2 = (char_t *) src2;
   }
   else
   {
      pch1 = (char_t *) src2;
      pch2 = (char_t *) src1;
   }

   if ((pch1 + n) <= pch2) /* check for address overlap */
   {
      for (; (0 != n); n--)
      {
         temp = *pch1;
         *pch1++ = *pch2;
         *pch2++ = temp;
      }
   }
}

/* 
 * Compare two strings, ignoring case
 */
int util_stricmp(const char *s1, const char *s2)
{
   char char_1;
   char char_2;
   int i;
   int results = 0;
   size_t len;

   PBC_Require((s1 != NULL) && (s2 != NULL), "util_stricmp called with NULL pointer");

   len = strlen(s1);

   /*Convert strings to lower case                                  */
   for (i = 0; (0 == results) && ((size_t)i <= len); i++)
   {
      char_1 = (char) tolower((unsigned char) s1[i]);
      char_2 = (char) tolower((unsigned char) s2[i]);
      results = strncmp(&char_1, &char_2, 1);
   }

   return results;
}

/* 
 * Allocate memory and duplicate string
 */
char *util_strdup(const char * str)
{
   char *dup_str = NULL;

   if (NULL != str)
   {
      dup_str = malloc(strlen(str) + 1);
      if (NULL != dup_str)
      {
         strcpy(dup_str, str);
      }
   }
   return dup_str;
}

/* 
 * Allocate memory and duplicate at most the elements
 * indicated by size parameter, the size of the duplicated 
 * string can be at most the size parameter plus 1 
 * (considering the end of string character will always be added 
 * to the duplicated string)
 */
char *util_strndup(const char * str, size_t size)
{
   char *dup_str = NULL;
   size_t str_len;

   if (NULL != str)
   {
      str_len = strlen(str);
      if (str_len > size)
      {
         str_len = size;
      }

      dup_str = malloc(str_len + 1);
      if (NULL != dup_str)
      {
         strncpy(dup_str, str, str_len);
         dup_str[str_len] = '\0';
      }
   }
   return dup_str;
}

/*===========================================================================*/
/*!
 * @file string_res.c
 *
 * @section RH REVISION HISTORY (top to bottom: last revision to first revision)
 *
 * - 25-Aug-2016 Vijayalakshmi KR Rev 2
 *   - Migrated the changes from kok_basa to ctc_ec
 *
 * - 05-Mar-2012 Kirk Bailey Rev 15
 *   - Added Safe_Strlen, Str_Full_Concat, Str_Full_Copy, Str_Is_Empty,
 *     Str_Partial_Concat, Str_Partial_Copy
 *   - Changed behavior of Str_Full_Copy (was Safe_Strncp) to not zero out entire
 *     buffer - only provides a single NUL terminator.
 *   - Formated source.
 *
 * - 15-Feb-2012 Kirk Bailey Rev 14
 *   - Added Safe_Strncat.
 *
 * - 26-Jan-2012 Kirk Bailey Rev 13
 *   - Added DISABLE_DEPRECATED_STRCPY, DISABLE_DEPRECATED_STRNCPY
 *   - Fixed bug where Str_Get_Sub_String accessed outside array bounds.
 *
 * - 12-Jul-2010 Larry Piekarski Rev 12
 *   - SCR kok_basa#2323 - Changed booleans to either bool_t or bool_fast
 *
 * - 21-apr-2010 Kirk Bailey Rev 11
 *   - Eliminated warnings issued by gcc 3.4.4.
 *
 * - 10-Dec-2009 Kirk Bailey Rev 10
 *   - kok_basa 3336: Added Safe_Strncpy.
 *
 * - 08-Jul-2009 Larry Piekarski Rev 9
 *   - Peer Review Updates
 *
 * - 25-Jun-2009 Jose Luis Pulido Rev 8
 *   - kok_aud#53431.- 023.- Create strdup and strndup reusable functions
 *
 * - 27-May-2009 Larry Piekarski Rev 7
 *   - Cleaned up code from review checklist
 *
 * - 21-May-2009 Larry Piekarski Rev 6
 *   - Fixed line endings
 *
 * - 13-Nov-2008 Jose Luis Pulido
 *   - Integrate Dan's new function to replace stricmp for uITRON (util_stricmp)
 *
 * - 12-Oct-2007 Dan Carman
 *   - QAC / MISRA changes
 *
 * - 18-Aug-2007 Dan Carman
 *   - MISRA changes
 *
 * - 19-Jun-2007 Bartosz Jamrozik
 *   - Added Str_Get_Sub_String and memexch functions inplementation
 *   - Added local function: copy_display_string, start_of_next_word, length_next_word
 *
 * - 22-May-2007 Bartosz Jamrozik
 *   - Created initial file.
 */
/*===========================================================================*/
