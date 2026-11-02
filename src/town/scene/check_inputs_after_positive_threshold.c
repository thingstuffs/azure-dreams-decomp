#include "common.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"
#include "town/player.h"

/* Check the supplied inputs only when the prerequisite value is positive. */
s32 check_inputs_after_positive_threshold(Rec_func_800165F4_arg0 *check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (sum_enabled_record_weights() > 0) {
        check_passed = apply_selected_entry_values(check_value, check_data) != 0;
    }
    return check_passed;
}
