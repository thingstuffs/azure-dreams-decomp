/* Relinked copy of town/func_80878260 (func_80878260.c); retail differs only at relocation sites. */
#include "common.h"

extern u8 D_00003F88[];
extern void advance_shop_entry_index_start(s32 index);
extern s32 test_indexed_flag_treating_indices(u16 value);

/* Select the first table entry whose value check returns zero. */
void select_table_entry_zero(void) {
    s32 index = 0;
    s32 offset = 0;

    while (test_indexed_flag_treating_indices(*(u16 *)&D_00003F88[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    advance_shop_entry_index_start(index);
}
