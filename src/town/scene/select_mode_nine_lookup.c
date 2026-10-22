#include "modules/town_ovl_3ef1c8.h"

/* Checks the input, then selects the mode-9 response with a state fallback or a fixed response. */
s32 select_mode_nine_lookup(s32 input, s32 context, s32 mode) {
    s32 result;

    if (check_table_result_below_minus_47(input, context) != 0) {
        return (s32)&D_8001B63C;
    }
    if (mode == 9) {
        invoke_handler_with_code_1470();
        result = func_80019ABC(&D_8001A9BC, &D_8001B1FC, input, 9);
        if (func_80019A04(&D_8001A9BC, input, 9) != 0) {
            result = select_state_result_with_lookup_overrides(input, context, 9);
        }
    } else {
        result = (s32)&D_8001D270;
    }
    return result;
}
