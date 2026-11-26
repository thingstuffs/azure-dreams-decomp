#include "common.h"
#include "town/data.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"
#include "town/scene/flags.h"
#include "town/shop/state.h"

extern u16 D_8070063A[5];
extern DevkitShopFlagLink D_80700650[3];

/* func_80700D74 is this image's copy of the shop flag test helper. */

/* Advance the entry at `index`: start its 0x278 step when eligible, otherwise run the entry's operation with 0 and return the index. */
s32 advance_devkit_entry_step_278(s32 index)
{
    if (func_80700D74(D_8070063A[0]) == 0 && func_80700D74(0x278) != 0) {
        if (func_807008FC(index) != 0) {
            set_linked_flag_80700cd0(D_80700650[index].first);
            clear_indexed_flag_bit_unless_index_one_80700d20(0x278);
            return dispatch_first_rejected_entry();
        }
        trigger_selected_entry_operation(index, 0);
        return index;
    }
    trigger_selected_entry_operation(index, 0);
    return index;
}
