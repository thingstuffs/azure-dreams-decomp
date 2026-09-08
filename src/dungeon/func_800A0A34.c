#include "common.h"

extern u32 D_800814A0[];
extern u32 D_800E296C[];
extern volatile u32 D_800E296C_reload[] __asm__("D_800E296C");

/* Advance the timed ramp to 255 and update completion and shutdown flags. */
void func_800A6194(void *ramp) {
    u16 ticks_left;
    u32 initial_flags;
    u32 current_flags;

    ticks_left = *(u16 *)((s8 *)ramp + 8) - 1;
    *(u16 *)((s8 *)ramp + 8) = ticks_left;
    if ((s16)ticks_left > 0) {
        *(s16 *)((s8 *)ramp + 10) += (0xFF - *(s16 *)((s8 *)ramp + 10)) / (s16)ticks_left;
    } else {
        *(s16 *)((s8 *)ramp + 10) = 0xFF;
        initial_flags = D_800E296C[0];
        *(u16 *)((s8 *)ramp + 8) = 0;
        D_800E296C[0] = initial_flags | 0x02000000;
    }
    current_flags = D_800E296C_reload[0];
    if (!(current_flags & 0x01000000)) {
        D_800E296C_reload[0] = current_flags & 0xFDFFFFFF;
        *(s16 *)((s8 *)ramp - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
