#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

/*
 * Applies the signed indexed entry value and returns one while F_sbs22_pad28 is set; otherwise
 * calls func_80019928.
 */
s32 dispatch_by_state_code_0x798(void *handler_arg_a, s32 handler_arg_b) {
    s32 result;

    if (func_8001A510(F_sbs22_pad28) == 0) {
        result = func_80019928(handler_arg_a, handler_arg_b);
    } else {
        apply_signed_value_to_indexed_entry(handler_arg_a, handler_arg_b);
        result = 1;
    }
    return result;
}
