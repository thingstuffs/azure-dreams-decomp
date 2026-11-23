#include "common.h"
#include "town/scene/record_actions.h"
#include "town/player.h"
#include "town/scene.h"

/* Check the supplied inputs only when the prerequisite value is at least 3. */
s32 apply_entry_values_at_weight_threshold(TownObjectSet *check_value, s32 check_data) {
    s32 check_passed;

    check_passed = 0;
    if (sum_enabled_record_weights() >= 3) {
        check_passed = apply_selected_entry_values(check_value, check_data) != 0;
    }
    return check_passed;
}
