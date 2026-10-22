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

void _spu_FsetRXX(s32 index, u32 value, s32 apply_shift);
s32 _spu_FsetRXXa(s32 index, u32 value);
s32 _spu_FgetRXXa(s32 index, s32 shift_mode);
void _spu_FsetPCR(s32 use_status_3);

#endif
