#ifndef SHARED_TOWN_EVENT_BUFFER_H
#define SHARED_TOWN_EVENT_BUFFER_H

/* Town event routines read and write four-byte records through this byte
 * buffer. The allocation extent is not independently established. */
extern unsigned char town_event_records[];

#endif
