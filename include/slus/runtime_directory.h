#ifndef SLUS_RUNTIME_DIRECTORY_H
#define SLUS_RUNTIME_DIRECTORY_H

#include "common.h"

/* Only the first 0x20 bytes are accessed by these functions. */
typedef struct {
    u32 value[8];
} GpTablePrefix;

extern s32 D_80080A6C;
extern GpTablePrefix D_8006B200;
extern GpTablePrefix D_8002D594;
extern u8 D_80082E6A[];
extern u8 D_80016000[];

extern void func_8003C6F8(s32 key, s32 index);

s32 func_8003C634(s32 key);
s32 func_8003C758(s32 key);
void func_8003C920(void);

#endif
