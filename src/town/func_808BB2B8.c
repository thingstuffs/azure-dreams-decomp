#include "common.h"

extern void func_80000C18(u16);
extern u8 D_00000000[];

void func_808BB2B8(void) {
    s32 i;

    for (i = 4; i < 8; i += 4) {
        func_80000C18(*(u16 *)(D_00000000 + i + 0xF10));
        func_80000C18(*(u16 *)(D_00000000 + i + 0xF12));
    }
}
