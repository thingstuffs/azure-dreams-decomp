/* Relinked copy of town/func_80878180 (func_80878180.c); retail differs only at relocation sites. */
#include "common.h"

extern u8 D_00003FB8[];
extern void func_80003BCC(s32);

/* Set flag 0x1F9 when the selected entry has bit 0 set. */
void func_800036D8(s32 row_index, s32 entry_index) {
    s32 offset;

    offset = (entry_index * 8) + (row_index << 5);
    if (*(s32 *) &D_00003FB8[offset] & 1) {
        func_80003BCC(0x1F9);
    }
}
