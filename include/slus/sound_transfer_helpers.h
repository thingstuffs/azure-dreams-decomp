#ifndef SLUS_SOUND_TRANSFER_HELPERS_H
#define SLUS_SOUND_TRANSFER_HELPERS_H

#include "common.h"

extern s32 D_80079980;
extern s32 D_8007998C;
extern s32 D_80079990;
extern s32 D_800794F4;
extern s32 D_800794EC;
extern u16 D_80079970;

s32 submitDriverTransferWithFallback(s32 channel, s32 playback_param);
s32 audioHandleOptionallyAlignsShiftsStoresReturnsResult(s32 index, u32 value);
s32 TestEvent(s32 event);
s32 clampAndSubmitDriverParameter(s32 voice, u32 rate);
s32 lookupAndScaleDriverAddress(s32 address);
s32 pollDriverCompletionEvent(s32 wait_for_completion);

#endif
