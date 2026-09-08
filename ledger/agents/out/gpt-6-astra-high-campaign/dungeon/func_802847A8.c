#include "common.h"

extern s8 D_800E2970[];

/* Clear the fields at offsets 0xA, 0xE, and 0x10 in all 36 entries. */
void func_800177A8(void) {
    s32 entry_index;
    s8 *entry;

    entry_index = 0x23;
    entry = D_800E2970;
    entry += 0x2BC;
    do {
        *(volatile s16 *)(entry + 0xA) = 0;
        *(volatile s16 *)(entry + 0xE) = 0;
        *(volatile s32 *)(entry + 0x10) = 0;
        entry -= 0x14;
    } while (--entry_index >= 0);
}
