/* Relinked copy of town/call_entry_has_bit_0 (call_entry_has_bit_0.c); it posts code 0x107 (twin 0x278), otherwise retail differs only at relocation sites. */
#include "common.h"

extern u8 D_00000DC4[];
extern void func_80000B40(s32);


/* Call func_80000B40 when the selected entry has bit 0 set. */
void func_800008F4(s32 row, s32 column) {
    s32 entry_offset;

    entry_offset = (column * 8) + (row << 4);
    if (*(s32 *)&D_00000DC4[entry_offset] & 1) {
        func_80000B40(0x107);
    }
}
