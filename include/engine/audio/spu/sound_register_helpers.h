#ifndef SLUS_SOUND_REGISTER_HELPERS_H
#define SLUS_SOUND_REGISTER_HELPERS_H
#include "sdk/libspu.h"

#include "common.h"

typedef volatile u16 SoundRegister16;

extern u16 *spu_registers;
extern volatile s32 *spu_dma_priority_register;
extern s32 spu_address_alignment_enabled;
extern s32 spu_address_unit_shift;
extern s32 spu_address_alignment;
extern s32 spu_address_alignment_mask;


#endif
