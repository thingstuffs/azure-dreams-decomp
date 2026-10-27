/* Stand-in declarations for the Psy-Q kernel event and memory card entry points. */
#ifndef SDK_LIBAPI_H
#define SDK_LIBAPI_H

#include "common.h"

s32 EnableEvent(u32 event);
s32 _card_info(s32 channel);

s32 open(char *path, s32 flags);
s32 close(s32 file);
u32 lseek(s32 file, u32 offset, s32 origin);
s32 read(s32 file, void *buffer, s32 size);
s32 write(s32 file, char *buffer, s32 size);

#endif
