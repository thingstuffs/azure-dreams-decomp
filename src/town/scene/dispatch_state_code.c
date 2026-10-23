#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

/*
 * Applies the signed indexed entry value and returns one while F_sbs22_pad28 is set; otherwise
 * calls func_80019928.
 */
s32 dispatch_by_state_code_0x798(s32 handler_arg_a, s32 handler_arg_b) {
    if (func_8001A510(F_sbs22_pad28) == 0) {
        func_80019928(handler_arg_a, handler_arg_b);
        return;
    }
    apply_signed_value_to_indexed_entry(handler_arg_a, handler_arg_b);
    return 1;
}
