#include "common.h"
#include "town/data.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/shop/state.h"

extern u16 D_A07009DE[];
extern DevkitShopFlagLink D_A0700A00[];

/* Advance the entry at `index`: start its 0x152 step when eligible, otherwise run the entry's operation with 0 and return the index. */
s32 advance_devkit_entry_step_152(s32 index)
{
    if (test_indexed_flag(D_A07009DE[0]) == 0 && test_indexed_flag(0x152) != 0) {
        if (test_flag_list_terminator(index) != 0) {
            set_indexed_flag(D_A0700A00[index].first);
            clear_indexed_flag(0x152);
            return select_first_unset_devkit_entry();
        }
        grid_run_bit_set_operation_b(index, 0);
        return index;
    }
    grid_run_bit_set_operation_b(index, 0);
    return index;
}
