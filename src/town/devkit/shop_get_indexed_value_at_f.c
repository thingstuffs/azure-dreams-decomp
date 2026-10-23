#include "common.h"

extern u8 devkit_globals_page[];
extern s32 devkit_shop_selection[3];

/* Return the value at 0x1F98 selected by the current signed index at 0x1FA4. */
s32 shop_get_indexed_value_at_1_f_98(void) {
    return *(s32 *)((u8 *)devkit_globals_page +
                    (*(s8 *)((u8 *)devkit_globals_page + devkit_shop_selection[0] + 0x1FA4) << 2) +
                    0x1F98);
}
