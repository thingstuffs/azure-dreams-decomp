#include "common.h"
#include "town/shop/state.h"
#include "town/devkit.h"
#include "town/data.h"

/* Select the first table entry whose value check returns zero. */
s32 advance_clear_flag_row(void) {
    s32 index = 0;

    while (test_indexed_flag(devkit_shop_flag_links[index].first) != 0) {
        index += 1;
    }
    return advance_selected_flag_row(index);
}
