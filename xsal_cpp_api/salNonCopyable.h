// ----------------------------------------------------------------------------
/**
 * @file    salNonCopyable.h
 *
 * @author  Wentao Li
 *
 * @author  2020 Syid Technologies, Inc., All Rights Reserved
 *          Information Contained Herein Is Proprietary and Confidential
 *
 * @brief   Definition of the NonCopyable class.
 */
 // ---------------------------------------------------------------------------

#ifndef XSAL_NONCOPYABLE_H
#define XSAL_NONCOPYABLE_H

namespace sal
{
   /**
    *  @class NonCopyable
    *  @brief NonCopyable class is a base class which prohibits
    *         copy construction and copy assignment.
    *
    *  An idea is taken from the C++ boost library http://www.boost.org.
    *  Derive your own class from NonCopyable when you want to prohibit copy
    *  construction and copy assignment.
    */
   class NonCopyable
   {
   protected:
      /**
       * @brief Constructor.
       *
       * @throw No throws.
       */
      NonCopyable();

      /**
       * @brief Destructor.
       *
       * @throw No throws.
       */
      ~NonCopyable();

   private:
      NonCopyable( const NonCopyable& );
      NonCopyable& operator=( const NonCopyable& );
   };

//////////////////////////////////////////////////////////////////////////////

   inline NonCopyable::NonCopyable()
   {
   }

//////////////////////////////////////////////////////////////////////////////

   inline NonCopyable::~NonCopyable()
   {
   }

//////////////////////////////////////////////////////////////////////////////

} // namespace sal

#endif // XSAL_NONCOPYABLE_H

/* ----------------------------------------------------------------------------
 * Revision history:
 *
 * 17 September 2020, Wentao Li (liwentao2005@126.com)
 *   Initial revision.
 *
 * --------------------------------------------------------------------------*/
