#include "modules/town_ovl_3ef1c8.h"

/*
 * Returns D_8001B7AE on the negative-threshold check; otherwise looks up D_8001A994 and
 * substitutes D_8001EDD0 when its follow-up check succeeds.
 */
s32 lookup_entry_with_default_fallback(s32 value, s32 check_value, s32 lookup_value) {
    s32 result;

    if (check_table_result_below_minus_47(value, check_value) != 0) {
        return (s32)&D_8001B7AE;
    }
    result = func_80019ABC(&D_8001A994, &scene_response_context, value, lookup_value);
    if (func_80019A04(&D_8001A994, value, lookup_value) != 0) {
        result = (s32)&D_8001EDD0;
    }
    return result;
}
