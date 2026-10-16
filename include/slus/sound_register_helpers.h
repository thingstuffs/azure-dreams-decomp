#ifndef SLUS_SOUND_REGISTER_HELPERS_H
#define SLUS_SOUND_REGISTER_HELPERS_H

#include "common.h"

typedef volatile u16 SoundRegister16;

extern u16 *D_80079958;
extern volatile s32 *D_80079968;
extern s32 D_8007997C;
extern s32 D_80079980;
extern s32 D_80079984;
extern s32 D_80079988;

void storeU16TableEntry(s32 index, u32 value, s32 apply_shift);
s32 audioHandleOptionallyAlignsShiftsStoresReturnsResult(s32 index, u32 value);
s32 loadU16TableEntryScaled(s32 index, s32 shift_mode);
void setDriverStatusBits(s32 use_status_3);

#endif
