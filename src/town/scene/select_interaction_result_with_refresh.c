#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/response_checks.h"
#include "town/scene.h"

/* Looks up a response, calls func_80019880, and uses the state fallback when the table check passes. */
s32 select_interaction_result_with_refresh(s32 input, s32 check_value, s32 context) {
    s32 result;

    if (check_table_result_below_minus_47() != 0) {
        return (s32)&scene_result_fallback;
    }
    result = func_80019ABC(&D_8001A96C, &scene_override_context, input, context);
    func_80019880();
    if (func_80019A04(&D_8001A96C, input, context) != 0) {
        result = select_state_result_with_lookup_overrides(input, check_value, context);
    }
    return result;
}
