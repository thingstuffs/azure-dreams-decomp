#include "modules/town_ovl_3ef1c8.h"

s32 select_scene_result_with_overrides(s32 context, s32 check_value, s32 selector) {
    s32 result;

    if (check_table_result_below_minus_47(context, check_value) != 0) {
        return (s32)&scene_result_fallback;
    }
    result = func_80019ABC(&D_8001A944, &scene_override_context, context, selector);
    if (func_80019A04(&D_8001A944, context, selector) != 0) {
        result = select_state_result_with_lookup_overrides(context, check_value, selector);
    }
    return result;
}
