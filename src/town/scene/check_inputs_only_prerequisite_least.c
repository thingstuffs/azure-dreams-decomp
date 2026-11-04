#include "common.h"
#include "town/scene/record_actions.h"
#include "town/player.h"

/* Check the supplied inputs only when the prerequisite value is at least 3. */
s32 check_inputs_only_prerequisite_least(Rec_func_800165F4_arg0 *check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (sum_enabled_record_weights() >= 3) {
        check_passed = apply_selected_entry_values(check_value, check_data) != 0;
    }
    return check_passed;
}
