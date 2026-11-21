#include "common.h"
#include "town/player.h"
#include "town/scene/flags.h"
#include "town/scene/record_actions.h"

/* Dispatches by status, converting the fallback handler result to a boolean. */
s32 apply_entry_values_by_enabled_weight(Rec_func_800165F4_arg0 *row, s32 entry_index) {
    s32 result;

    if (sum_enabled_record_weights() >= 2) {
        return replace_record_flag_with_entry_flag(row, entry_index);
    }
    result = 0;
    if (sum_enabled_record_weights() > 0) {
        result = apply_selected_entry_values(row, entry_index) != 0;
    }
    return result;
}
