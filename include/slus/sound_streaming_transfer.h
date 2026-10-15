#ifndef SLUS_SOUND_STREAMING_TRANSFER_H
#define SLUS_SOUND_STREAMING_TRANSFER_H

#include "common.h"

extern s32 D_800799C0[10];
extern s32 D_80079974;
extern s32 D_80079970[4];
extern s32 D_80079980;
extern s32 D_80079990[3];
extern s32 D_80079988[3];
extern volatile s32 D_8007998C[3];
extern u8 D_80079550[];
extern s32 D_800794EC;

extern s32 func_8005D9DC(u32 value);
extern s32 func_8005D1D0(s32 mode, ...);
extern s32 WaitEvent(s32 event);

s32 func_8005E7E0(s32 voice);

#endif
