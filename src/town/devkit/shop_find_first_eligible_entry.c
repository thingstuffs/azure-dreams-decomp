#include "common.h"
#include "town/shop/state.h"

extern u8 devkit_shop_flag_links[];
extern s32 advance_selected_flag_row(s32 index);

/* Select the first table entry whose value check returns zero. */
s32 advance_clear_flag_row(void) {
    s32 index = 0;
    s32 offset = 0;

    while (test_linked_flag(*(u16 *)&devkit_shop_flag_links[offset]) != 0) {
        offset += 4;
        index += 1;
    }
    return advance_selected_flag_row(index);
}
