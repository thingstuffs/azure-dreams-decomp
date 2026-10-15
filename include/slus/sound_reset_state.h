#ifndef SLUS_SOUND_RESET_STATE_H
#define SLUS_SOUND_RESET_STATE_H

#include "slus/sound_range_records.h"

extern s32 D_800799C0[10];
extern s16 D_80079520[24];
extern s32 D_800794F8;
extern s32 D_800794FC;
extern s32 D_80079508;
extern u16 D_8007950C;
extern u16 D_8007950E;
extern s32 D_80079510;
extern s32 D_80079514;
extern u32 D_80079500;
extern s32 D_800794F4;
extern s32 D_80079974;
extern s32 D_800794F0;
extern s32 D_8007951C;
extern s32 D_80079518;
extern s32 D_80079950;
void ResetCallback(s32 channel);
s32 func_8005CC04(s32 warm);
void func_8005CB88(void);
void storeU16TableEntry(s32 index, u32 value, s32 apply_shift);

void func_8005CA90(s32 channel);
s32 func_8005E450(s32 enabled);

#endif
