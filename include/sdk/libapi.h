/* Stand-in declarations for the Psy-Q kernel event and memory card entry points. */
#ifndef SDK_LIBAPI_H
#define SDK_LIBAPI_H

#include "common.h"

s32 EnableEvent(u32 event);
s32 _card_info(s32 channel);

#endif
