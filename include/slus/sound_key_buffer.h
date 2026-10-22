#ifndef SLUS_SOUND_KEY_BUFFER_H
#define SLUS_SOUND_KEY_BUFFER_H
#include "common.h"

typedef struct {
    u8 pad[0x188];
    volatile u16 keyon_lo;
    volatile u16 keyon_hi;
    u16 keyoff_lo;
    u16 keyoff_hi;
} SpuKeyRegs;

extern u16 *spu_registers;
extern u16 spu_register_shadow[];
extern s32 spu_register_buffer_flags;
extern volatile s32 spu_active_voice_mask;
extern volatile s32 spu_buffered_voice_mask;
extern volatile s32 spu_register_dirty_flags;
extern volatile u16 spu_keyon_shadow[];
extern volatile u16 spu_keyoff_low_shadow;
extern volatile u16 spu_keyoff_high_shadow;
u32 modify_spu_register_bit_pair(s32 mode, u32 value, s32 low_index, s32 high_index);
void SpuSetKey(s32 key_on, u32 voices);

#endif
