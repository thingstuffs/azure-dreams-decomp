#include "common.h"
#include "town/data.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/shop/state.h"

extern DevkitShopFlagLink D_A0700A00[];

/* Find the first entry whose flag is clear and advance its step. */
s32 select_first_unset_devkit_entry(void)
{
    s32 index = 0;

    while (test_indexed_flag(D_A0700A00[index].first) != 0) {
        index += 1;
    }
    return advance_devkit_entry_step_152(index);
}
