#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/player/state.h"

/*
 * Applies the signed indexed entry value and returns one while F_sbs22_pad28 is set; otherwise
 * calls func_80019928.
 */
s32 dispatch_by_state_code_0x798(void *handler_arg_a, s32 handler_arg_b) {
    s32 result;

    if (get_script_flag_mask(F_sbs22_pad28) == 0) {
        result = process_checked_entry(handler_arg_a, handler_arg_b);
    } else {
        set_flag_from_indexed_entry(handler_arg_a, handler_arg_b);
        result = 1;
    }
    return result;
}
