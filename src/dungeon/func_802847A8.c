#include "common.h"

extern s8 D_800E2970[];

void func_800177A8(void) {
    s32 i;
    s8 *entry;

    i = 0x23;
    entry = D_800E2970;
    entry += 0x2BC;
    do {
        *(volatile s16 *)(entry + 0xA) = 0;
        *(volatile s16 *)(entry + 0xE) = 0;
        *(volatile s32 *)(entry + 0x10) = 0;
        entry -= 0x14;
    } while (--i >= 0);
}
