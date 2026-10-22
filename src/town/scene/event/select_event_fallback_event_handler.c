#include "modules/town_ovl_3ef1c8.h"

/* Selects event response data, using progress-based dialogue overrides when the object's flag is set. */
s32 select_event_fallback_event_handler(s32 object, s32 request, s32 context) {
    s32 default_result;
    s32 result;

    if (check_table_result_below_minus_47(object, request, context) != 0) {
        return (s32)((u8 *)&D_8001B63C);
    }
    default_result = func_80019ABC(&D_8001A9AC, &D_8001B1F8, object, context);
    result = default_result;
    if (func_80019A04(&D_8001A9AC, object, context) != 0) {
        if (func_8001A510(((S_8001747C_0 *)object)->unk_18) != 0) {
            result = select_state_result_with_lookup_overrides(object, request, context);
        } else {
            result = (s32)((u8 *)&D_8001CFB4);
        }
    }
    return result;
}
