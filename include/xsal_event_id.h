#ifndef XSAL_EVENT_ID_H
#   define XSAL_EVENT_ID_H
/**
 * System wide event identifiers.
 *
 * All published event identifiers need to be listed in this typedef between
 * SAL_EVG_FIRST_PUBLISHED_EVENT_ID and SAL_EVG_LAST_PUBLISHED_EVENT_ID.
 *
 * Public events are those that are shared between modules but are not
 * available for use with SAL_Publish() and SAL_Subscribe(). These are assigned
 * values between SAL_EVG_LAST_PUBLISHED_EVENT_ID and SAL_EV_FIRST_PRIVATE_ID.
 *
 * Tasks can use private event IDs starting at SAL_EV_FIRST_PRIVATE_ID. Private
 * events include timer IDs, internal message sent via SAL_Send(), etc.
 */
typedef enum SAL_Event_Id_Tag
{
   /** RESERVED for XSAL, must be first; do not change! */
   SAL_FIRST_EVENT_ID = 0,
   SAL_EVG_FIRST_PUBLISHED_EVENT_ID = SAL_FIRST_EVENT_ID,

   SAL_PUBLISHED_EVENTS,

   /** RESERVED for XSAL, must be last published event id; do not change! */
   SAL_EVG_LAST_PUBLISHED_EVENT_ID,

   SAL_PUBLIC_EVENTS,

   /** First private event identifier value. */
   SAL_EV_FIRST_PRIVATE_ID,

   SAL_PRIVATE_EVENTS,

   SAL_LAST_EVENT_ID /* Must be last - do not move! */
}
SAL_Event_Id_T;

#endif