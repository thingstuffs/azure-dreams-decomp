#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

/*
 * Calls func_80019928 while F_sbs22_pad28 is set; otherwise applies the signed indexed entry value
 * and returns one.
 */
s32 dispatch_entry_by_798_state(s32 handler_arg_a, s32 handler_arg_b) {
    if (func_8001A510(F_sbs22_pad28) != 0) {
        func_80019928(handler_arg_a, handler_arg_b);
        return;
    }
    apply_signed_value_to_indexed_entry(handler_arg_a, handler_arg_b);
    return 1;
}
