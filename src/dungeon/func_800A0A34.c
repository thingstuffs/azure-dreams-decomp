#include "common.h"

extern u32 D_800814A0[];
extern u32 D_800E296C[];
extern volatile u32 D_800E296C_reload[] __asm__("D_800E296C");

void func_800A6194(void *arg0) {
    u16 temp_v0;
    u32 initial_flags;
    u32 current_flags;

    temp_v0 = *(u16 *)((s8 *)arg0 + 8) - 1;
    *(u16 *)((s8 *)arg0 + 8) = temp_v0;
    if ((s16)temp_v0 > 0) {
        *(s16 *)((s8 *)arg0 + 10) += (0xFF - *(s16 *)((s8 *)arg0 + 10)) / (s16)temp_v0;
    } else {
        *(s16 *)((s8 *)arg0 + 10) = 0xFF;
        initial_flags = D_800E296C[0];
        *(u16 *)((s8 *)arg0 + 8) = 0;
        D_800E296C[0] = initial_flags | 0x02000000;
    }
    current_flags = D_800E296C_reload[0];
    if (!(current_flags & 0x01000000)) {
        D_800E296C_reload[0] = current_flags & 0xFDFFFFFF;
        *(s16 *)((s8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
