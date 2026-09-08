#include "common.h"

extern void func_80000C18(u16);
extern u8 D_00000000[];

/* Pass a pair of 16-bit table values to func_80000C18. */
void func_808BB2B8(void) {
    s32 pair_offset;

    for (pair_offset = 4; pair_offset < 8; pair_offset += 4) {
        func_80000C18(*(u16 *)(D_00000000 + pair_offset + 0xF10));
        func_80000C18(*(u16 *)(D_00000000 + pair_offset + 0xF12));
    }
}
