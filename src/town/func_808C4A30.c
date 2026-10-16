/* Relinked copy of town/func_808BB2B8 (func_808BB2B8.c); retail differs only at relocation sites. */
#include "common.h"

extern void func_80000B90(u16);
extern u8 D_FFFFFE94[];

/* Pass a pair of 16-bit table values to func_80000B90. */
void func_80000A30(void) {
    s32 pair_offset;

    for (pair_offset = 4; pair_offset < 8; pair_offset += 4) {
        func_80000B90(*(u16 *)(D_FFFFFE94 + pair_offset + 0xF10));
        func_80000B90(*(u16 *)(D_FFFFFE94 + pair_offset + 0xF12));
    }
}
