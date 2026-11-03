#include "common.h"
#include "town/scene/flags.h"
#include "town/shop/state.h"
#include "town/devkit.h"
#include "town/devkit/flag_test_imports.h"

typedef struct {
    u16 value;
    u16 pad;
} Entry4;

extern u16 D_8070063A[5];
extern u16 D_80700658[5];
extern u16 D_8070065C[5];
extern u16 D_80700660[5];
extern Entry4 D_80700650[3];

/* Clear the pending flags for the index's stage and return the follow-up handler's result. */
s32 finish_stage_for_index(s32 index) {
    if (func_80700D74(D_8070063A[0]) == 0 &&
        func_80700D74(0x278) != 0 &&
        func_807008FC(index) != 0) {
        if (func_80700D74(0x281) != 0) {
            clear_indexed_flag_bit_unless_index_one_80700d20(D_80700658[0]);
            clear_indexed_flag_bit_unless_index_one_80700d20(D_8070065C[0]);
            clear_indexed_flag_bit_unless_index_one_80700d20(D_80700660[0]);
            clear_indexed_flag_bit_unless_index_one_80700d20(0x281);
            clear_indexed_flag_bit_unless_index_one_80700d20(0x280);
            clear_indexed_flag_bit_unless_index_one_80700d20(0x278);
            return dispatch_first_rejected_entry();
        }

        if (func_80700D74(0x288) != 0) {
            set_linked_flag_80700cd0(D_80700650[index].value);
            clear_indexed_flag_bit_unless_index_one_80700d20(0x278);
            return dispatch_first_rejected_entry();
        }
    }

    func_8070096C(index, 0);
    return index;
}
