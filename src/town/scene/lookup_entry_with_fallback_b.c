#include "modules/town_ovl_3ef1c8.h"

/*
 * Returns scene_result_fallback on the negative-threshold check; otherwise queries D_8001A9B4 with
 * scene_response_context and uses lookup overrides when the follow-up check succeeds.
 */
s32 lookup_entry_with_fallback_b(s32 context, s32 check_value, s32 selector) {
    s32 result;

    if (check_table_result_below_minus_47(context, check_value) != 0) {
        return (s32)&scene_result_fallback;
    }
    result = func_80019ABC(&D_8001A9B4, &scene_response_context, context, selector);
    if (func_80019A04(&D_8001A9B4, context, selector) != 0) {
        result = select_state_result_with_lookup_overrides(context, check_value, selector);
    }
    return result;
}
