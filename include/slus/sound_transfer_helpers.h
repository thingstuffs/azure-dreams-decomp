#ifndef SLUS_SOUND_TRANSFER_HELPERS_H
#define SLUS_SOUND_TRANSFER_HELPERS_H

#include "common.h"

extern s32 D_80079980;
extern s32 D_8007998C;
extern s32 D_80079990;
extern s32 D_800794F4;
extern s32 D_800794EC;
extern u16 D_80079970;

s32 func_8005D460(s32 channel, s32 playback_param);
s32 func_8005D598(s32 index, u32 value);
s32 TestEvent(s32 event);
s32 func_8005EC40(s32 voice, u32 rate);
s32 func_8005ECA0(s32 address);
s32 func_8005ECF8(s32 wait_for_completion);

#endif
