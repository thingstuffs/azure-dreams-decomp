#include "common.h"
#include "town/player.h"
#include "town/scene/flags.h"

s32 apply_selected_entry_values(s32, s32);

/* Dispatches by status, converting the fallback handler result to a boolean. */
s32 apply_entry_values_by_enabled_weight(s32 handler_arg, s32 handler_param) {
    s32 result;

    if (sum_enabled_record_weights() >= 2) {
        return replace_record_flag_with_entry_flag(handler_arg, handler_param);
    }
    result = 0;
    if (sum_enabled_record_weights() > 0) {
        result = apply_selected_entry_values(handler_arg, handler_param) != 0;
    }
    return result;
}
