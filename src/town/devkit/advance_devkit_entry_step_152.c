#include "common.h"
#include "town/data.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/shop/state.h"

extern u16 D_A07009DE[];
extern DevkitShopFlagLink D_A0700A00[];

/* func_A0700750, func_A07006AC and func_A07006FC are this image's copies of the shop flag test, set and clear helpers.
   func_A0700348 runs an entry's operation (the home is grid_run_bit_set_operation_b). func_A07002D8 takes the entry index
   and its role is not identified here. */

/* Advance the entry at `index`: start its 0x152 step when eligible, otherwise run the entry's operation with 0 and return the index. */
s32 advance_devkit_entry_step_152(s32 index)
{
    if (func_A0700750(D_A07009DE[0]) == 0 && func_A0700750(0x152) != 0) {
        if (func_A07002D8(index) != 0) {
            func_A07006AC(D_A0700A00[index].first);
            func_A07006FC(0x152);
            return select_first_unset_devkit_entry();
        }
        func_A0700348(index, 0);
        return index;
    }
    func_A0700348(index, 0);
    return index;
}
