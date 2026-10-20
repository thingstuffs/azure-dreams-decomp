#ifndef SLUS_SOUND_TRANSFER_FRONTENDS_H
#define SLUS_SOUND_TRANSFER_FRONTENDS_H

#include "common.h"

extern u16 D_80079970;
extern s32 D_80079974;
extern s32 D_80079980;

s32 func_8005D1D0(s32 command, ...);
void func_8005CE98(u16 *src, u32 bytes_left);
s32 submit_driver_transfer_with_fallback(s32 channel, s32 playback_param);
s32 submit_driver_transfer_mode_zero(s32 buffer_addr, s32 size);

#endif
