#ifndef SLUS_SOUND_REGISTER_HELPERS_H
#define SLUS_SOUND_REGISTER_HELPERS_H

#include "common.h"

typedef volatile u16 SoundRegister16;

extern u16 *spu_registers;
extern volatile s32 *spu_dma_priority_register;
extern s32 spu_address_alignment_enabled;
extern s32 spu_address_unit_shift;
extern s32 spu_address_alignment;
extern s32 spu_address_alignment_mask;

void store_u16_table_entry(s32 index, u32 value, s32 apply_shift);
s32 audio_handle_optionally_aligns_shifts_stores_returns_result(s32 index, u32 value);
s32 load_u16_table_entry_scaled(s32 index, s32 shift_mode);
void set_driver_status_bits(s32 use_status_3);

#endif
