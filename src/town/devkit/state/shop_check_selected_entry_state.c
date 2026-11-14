#include "common.h"
#include "town/shop/state.h"


/* Return 2 when the selected flag is set and flag 0x1F9 is clear. */
s32 get_selected_flag_state(s32 unused_selection) {
    s32 result;

    result = 0;
    if (test_indexed_flag(*(u16 *)0x80701DCE) != 0) {
        result = (test_indexed_flag(0x1F9U) == 0) * 2;
    }
    return result;
}
