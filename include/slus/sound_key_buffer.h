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

extern u16 *D_80079958;
extern u16 D_80086BD0[];
extern s32 D_80079950;
extern volatile s32 D_800794F0;
extern volatile s32 D_80079518;
extern volatile s32 D_8007951C;
extern volatile u16 D_80086D58[];
extern volatile u16 D_80086D5C;
extern volatile u16 D_80086D5E;
u32 func_8005E4C4(s32 mode, u32 value, s32 low_index, s32 high_index);
void func_8005E97C(s32 key_on, u32 voices);

#endif
