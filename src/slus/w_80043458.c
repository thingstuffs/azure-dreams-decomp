#include "common.h"

/* Reset global state and clear flags in the primary and secondary entry arrays. */
void func_80043458(void) {
    u8 *base;
    s32 i;

    base = (u8 *)0x80010000;
    *(s32 *)(base + 0x208C) = 0;
    *(s32 *)(base + 0x2090) = 0;
    base[0x2D52] = 0xFF;
    base[0x2D53] = 0xFF;
    base[0x21E0] = 0xFF;
    base[0x21E1] = 0xFF;
    for (i = 0; i < 20; i++) {
        base[0x24B + i * 4] &= 0x5F;
        *(s32 *)(base + 0x304 + i * 0x54) &= ~0x4000;
    }
    base = (u8 *)0x80010000;
    for (i = 0; i < 64; i++) {
        *(s32 *)(base + 0xA94 + i * 0x54) &= ~0x4000;
    }
}
