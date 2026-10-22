#include "modules/town_ovl_3ef1c8.h"

/* Looks up a response, applies the helper-result >= 10 override, then checks for a state fallback. */
s32 select_lookup_with_count_threshold(s32 object, s32 check_value, s32 selection) {
    s32 response;

    if (check_table_result_below_minus_47(object, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    response = func_80019ABC(&D_8001A954, &D_8001B1F8, object, selection);
    if (func_8001A7F8() >= 10) {
        func_80019880();
        response = (s32)&D_800211DC;
    }
    if (func_80019A04(&D_8001A954, object, selection) != 0) {
        response = select_state_result_with_lookup_overrides(object, check_value, selection);
    }
    return response;
}
