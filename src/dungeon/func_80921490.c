#include "common.h"

void func_800F6490(void) {
    s32 i;
    u32 page;
    s32 c13;
    s32 c2;
    volatile u32 *entry;
    volatile u8 *p;
    u32 idx;

    i = 0x3F;
    page = 0x80010000;
    c13 = 0x13;
    c2 = 2;
    entry = (volatile u32 *)(page | 0xA7C);
    p = (volatile u8 *)(page | 0xFC);
    do {
        if (p[0x981] == c13 && p[0x980] == c2) {
            idx = p[0x983] & 0x3F;
            ((u8 *)page)[idx * 0x54 + 0xA93] = 0;
            *entry = 0;
        }
        entry--;
        i--;
        p -= 4;
    } while (i >= 0);
}
