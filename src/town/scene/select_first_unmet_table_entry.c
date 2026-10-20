/* Relinked copy of town/func_80878260 (func_80878260.c); retail differs only at relocation sites. */
#include "common.h"

extern u8 D_00000DB4[];
extern void advance_shop_entry_index_107(s32 index);
extern s32 func_80000BE4(u16 value);

/* Select the first table entry whose value check returns zero. */
void select_first_unmet_table_entry(void) {
    s32 index = 0;
    s32 offset = 0;

    while (func_80000BE4(*(u16 *)&D_00000DB4[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    advance_shop_entry_index_107(index);
}
