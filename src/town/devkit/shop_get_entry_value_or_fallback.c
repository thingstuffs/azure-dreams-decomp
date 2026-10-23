#include "common.h"
#include "m2c_compat.h"

extern s32 devkit_globals_page[];
extern s32 D_807014C8[];
extern s32 D_80701DC4[];
extern s32 devkit_shop_selection[];

extern void set_entry_bit_flag(s32 index, s32 entry_index);

/* Returns the current entry value or fallback address after calling shop_set_entry_step_flag. */
s32 read_flag_row_fallback(void) {
    s32 selected_value;
    if (devkit_shop_selection[0] == 0) {
        selected_value = *(s32 *)((u8 *)devkit_globals_page + (D_80701DC4[0] << 5) + 0x1E30);
    } else {
        selected_value = (s32)D_807014C8;
    }
    set_entry_bit_flag(D_80701DC4[0], 1);
    return selected_value;
}
