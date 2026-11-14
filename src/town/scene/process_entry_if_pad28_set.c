#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/scene.h"
#include "town/player/state.h"

/*
 * Calls func_80019928 while F_sbs22_pad28 is set; otherwise applies the signed indexed entry value
 * and returns one.
 */
s32 process_entry_if_pad28_set(void *handler_arg_a, s32 handler_arg_b) {
    s32 result;

    if (get_script_flag_mask(F_sbs22_pad28) != 0) {
        result = process_checked_entry(handler_arg_a, handler_arg_b);
    } else {
        set_flag_from_indexed_entry(handler_arg_a, handler_arg_b);
        result = 1;
    }
    return result;
}
