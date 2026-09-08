#include "common.h"

extern u8 D_00000F48[];
extern void func_80000BC8(s32);

__asm__(".set D_00000F48, 0xF48");

/* Call func_80000BC8 when the selected entry has bit 0 set. */
void func_808BB058(s32 row, s32 column) {
    s32 entry_offset;

    entry_offset = (column * 8) + (row << 4);
    if (*(s32 *)&D_00000F48[entry_offset] & 1) {
        func_80000BC8(0x278);
    }
}
