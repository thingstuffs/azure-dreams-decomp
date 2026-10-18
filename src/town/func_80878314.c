#include "common.h"

s32 shop_test_indexed_flag();                             /* extern */

/* Return 2 when the selected flag is set and flag 0x1F9 is clear. */
s32 shop_check_selected_entry_state(void) {
    s32 result;

    result = 0;
    if (shop_test_indexed_flag(*(u16 *)0x80701DCE) != 0) {
        result = (shop_test_indexed_flag(0x1F9U) == 0) * 2;
    }
    return result;
}
