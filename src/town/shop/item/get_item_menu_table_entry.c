#include "common.h"
#include "town/shop/item.h"

extern s32 D_800D156C[];

/* Returns the table entry at the given index. */
s32 get_item_menu_table_entry(s32 index) {
    return D_800D156C[index];
}
