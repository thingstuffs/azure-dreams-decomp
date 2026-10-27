#ifndef SDK_MEMORY_H
#define SDK_MEMORY_H

#include "common.h"

void *memcpy(void *dest, const void *source, u32 size);
void *memmove(void *dest, const void *source, s32 size);
void *memset(void *dest, s32 value, s32 size);
void bzero(void *buffer, s32 size);

#endif
