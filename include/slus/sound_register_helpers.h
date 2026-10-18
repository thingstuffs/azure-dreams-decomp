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

void store_u16_table_entry(s32 index, u32 value, s32 apply_shift);
s32 audio_handle_optionally_aligns_shifts_stores_returns_result(s32 index, u32 value);
s32 load_u16_table_entry_scaled(s32 index, s32 shift_mode);
void set_driver_status_bits(s32 use_status_3);

#endif
