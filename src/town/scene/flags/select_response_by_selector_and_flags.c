#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene/response_checks.h"
#include "town/scene/flags.h"

/* Chooses response data using the selector, checked status, and progress flags, with an alternate handler. */
s32 *select_response_by_selector_and_flags(s32 context, s32 check_value, s32 selector) {
    s32 *response;

    if (selector == 9) {
        if (check_table_result_below_minus_47() != 0) {
            if (func_8001A510(F_sbs22_pad28) != 0) {
                return &D_8001B6D0;
            }
            if (func_8001A510(F_sbs04_pad07) == 0) {
                return &scene_result_fallback;
            }
        }
        response = func_80019ABC((u8 *)&D_8001A974, &scene_response_context, context, selector);
        if (func_80019A04((u8 *)&D_8001A974, context, selector) != 0) {
            response = &D_8001C64E;
        }
    } else if (selector == 1) {
        response = &D_8001B824;
    } else {
        invoke_alternate_handler_with_code_7_a_1();
        response = &D_8001C5FB;
    }
    return response;
}
