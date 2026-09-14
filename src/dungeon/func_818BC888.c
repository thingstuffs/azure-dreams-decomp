#include "common.h"

typedef struct S_818BC888_0_pre {
    u16 unk_00;
} S_818BC888_0_pre;   /* the 0x2 bytes before arg0 in func_818BC888, addressed as arg0[-1] */

typedef struct S_818BC888_0 {
    void * unk_00;
    union { u16 u16; s16 s16; u8 u8; } unk_04;   /* accessed as both */
    u8 pad_06[0x2];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 unk_0E;
} S_818BC888_0;   /* arg0 in func_818BC888 */

typedef struct S_818BC888_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818BC888_1;   /* temp_v1 in func_818BC888 */



extern s32 D_800814A0[3];

/* Advances the effect timer and updates its interpolated and cycling values. */
void func_818BC888(void *effect) {
    s16 phase;
    s32 cycle_value;
    s32 scaled_step;
    u16 tick;
    s32 ticks;
    u32 scaled_value;
    u32 product;
    S_818BC888_1 *owner;

    owner = ((S_818BC888_0 *)effect)->unk_00;
    owner->unk_14 = owner->unk_14 + 1;
    tick = ((S_818BC888_0 *)effect)->unk_04.u16 + 1;
    ((S_818BC888_0 *)effect)->unk_04.u16 = tick;
    ticks = (s16)tick;
    scaled_step = ((S_818BC888_0 *)effect)->unk_0A << 0xB;
#ifndef NON_MATCHING
    if (ticks >= 0x20) {
        product = (0x40 - ticks) * scaled_step;
    } else {
        product = ticks * scaled_step;
    }
#else
    product = (s16)tick * scaled_step;
#endif
    scaled_value = product >> 0x10;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_818BC888_0 *)effect)->unk_08 = scaled_value;
    phase = ((S_818BC888_0 *)effect)->unk_04.s16;
    if (phase >= 0x40) {
        ((S_818BC888_0_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (phase < 0x10) {
        ((S_818BC888_0 *)effect)->unk_0E = ((S_818BC888_0 *)effect)->unk_04.u8 << 3;
    } else if (phase < 0x30) {
        ((S_818BC888_0 *)effect)->unk_0E = 0x80;
    } else {
        ((S_818BC888_0 *)effect)->unk_0E = -0x80 - ((phase - 0x30) * 8);
    }

    phase = ((S_818BC888_0 *)effect)->unk_04.s16 % 4;
    switch (phase) {
    case 0:
        cycle_value = 0x7DCF;
        break;
    case 1:
        cycle_value = 0x7E00;
        break;
    case 2:
        cycle_value = 0x7E01;
        break;
    case 3:
        cycle_value = 0x7E02;
        break;
    default:
        return;
    }
    ((S_818BC888_0 *)effect)->unk_0C = cycle_value;
}
