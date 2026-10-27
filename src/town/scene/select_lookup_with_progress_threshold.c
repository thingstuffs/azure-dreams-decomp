#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/response_checks.h"

/* Looks up a response, applies the helper-result >= 5 override, then checks for a state fallback. */
void *select_lookup_with_progress_threshold(s32 selector, s32 check_value, s32 lookup_value) {
    void *result;

    if (check_table_result_below_minus_47() != 0) {
        return &scene_result_fallback;
    }
    result = func_80019ABC(&D_8001A94C, &scene_override_context, selector, lookup_value);
    if (func_8001A7F8() >= 5) {
        func_80019880();
        result = &D_80020E5C;
    }
    if (func_80019A04(&D_8001A94C, selector, lookup_value) != 0) {
        result = select_state_result_with_lookup_overrides(selector, check_value, lookup_value);
    }
    return result;
}
