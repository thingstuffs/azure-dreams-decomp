#include "common.h"

extern u8 devkit_globals_page[];
extern s32 devkit_shop_selection[3];

/* Return the table value indexed by the current signed byte entry. */
s32 shop_get_current_entry_value(void) {
    return *(s32 *)((u8 *)devkit_globals_page +
                    (*(s8 *)((u8 *)devkit_globals_page + devkit_shop_selection[0] + 0x1F94) << 2) +
                    0x1F88);
}
