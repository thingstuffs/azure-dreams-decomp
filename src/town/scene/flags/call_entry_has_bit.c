#include "common.h"
#include "town/scene/flags.h"

extern u8 D_00000F48[];
extern void func_80000BC8(s32);


/* Call func_80000BC8 when the selected entry has bit 0 set. */
void call_entry_has_bit_0(s32 row, s32 column) {
    s32 entry_offset;

    entry_offset = (column * 8) + (row << 4);
    if (*(s32 *)&D_00000F48[entry_offset] & 1) {
        func_80000BC8(0x278);
    }
}
