#ifndef SLUS_JTBL_8005F134_H
#define SLUS_JTBL_8005F134_H

#include "common.h"
#include "shared/spu_voice.h"

extern volatile u16 *D_80079958;
extern u16 D_80079520[24];
extern s32 D_800794F0;
extern s32 D_80079980;

u32 func_8005F7D0(u16 center_note, u16 center_fine, u16 note, u16 fine);
u32 soundConvertPitchToPackedNote(u16 center_note, u16 center_fine, u16 pitch);
s32 audioHandleOptionallyAlignsShiftsStoresReturnsResult(s32 reg, u32 val);
s32 func_8005EB78(s32 voice_mask);
void func_8005F134(SpuVoiceAttr_ *attr);
void func_8005FA34(SpuVoiceAttr_ *voice_attr);

#endif
