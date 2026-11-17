#include "common.h"
#include "m2c_compat.h"
#include "town/shop/state.h"
#include "town/devkit.h"
#include "town/data.h"

extern s16 *D_80701DEC[];

/* Skips entries accepted by shop_test_indexed_flag and checks whether the next entry is zero. */
s32 test_flag_list_terminator(s32 list_index) {
    s16 *entry;

    entry = D_80701DEC[devkit_shop_flag_links[list_index].next];
    while (test_indexed_flag(*entry) != 0) {
        entry += 1;
    }
    return *entry == 0;
}
