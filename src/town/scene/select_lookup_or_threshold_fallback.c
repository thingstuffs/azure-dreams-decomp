#include "modules/town_ovl_3ef1c8.h"

s32 select_lookup_or_threshold_fallback(s32 value, s32 check_value, s32 lookup_value) {
    s32 result;

    if (check_table_result_below_minus_47(value, check_value) != 0) {
        return (s32)&D_8001B6D0;
    }
    result = func_80019ABC(&D_8001A984, &scene_response_context, value, lookup_value);
    if (func_80019A04(&D_8001A984, value, lookup_value) != 0) {
        result = (s32)&D_8001F560;
    }
    return result;
}
