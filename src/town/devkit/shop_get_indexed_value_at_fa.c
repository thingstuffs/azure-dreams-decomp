#include "common.h"

extern u8 devkit_globals_page[];
extern s32 devkit_shop_selection[3];

/* Return the value at 0x1FA8 selected by the current signed index at 0x1FB4. */
s32 shop_get_indexed_value_at_1_fa_8(void) {
    return *(s32 *)(devkit_globals_page +
                    (*(s8 *)(devkit_globals_page + devkit_shop_selection[0] + 0x1FB4) << 2) +
                    0x1FA8);
}
