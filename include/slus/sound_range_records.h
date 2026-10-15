#ifndef SLUS_SOUND_RANGE_RECORDS_H
#define SLUS_SOUND_RANGE_RECORDS_H

#include "common.h"

typedef struct S_800799BC {
    u32 flags;
    u32 size;
} S_800799BC;

extern s32 D_80079980;
extern s32 D_800799B4;
extern s32 D_800799B8;
extern S_800799BC *D_800799BC;

s32 func_8005D838(s32 count, S_800799BC *record);
s32 func_8005D95C(u32 address);
s32 func_8005D9DC(u32 value);

#endif
