#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

#include "town/scene/record_actions.h"

/*
 * Sets the indexed entry flag and returns one only while F_s24_door_open has a nonzero script flag
 * mask.
 */
s32 dispatch_if_condition_1463(Rec_func_800165F4_arg0 *dispatch_value, s32 dispatch_option) {
    if (get_script_flag_mask(F_s24_door_open) != 0) {
        set_indexed_entry_flag(dispatch_value, dispatch_option);
        return 1;
    }
    return 0;
}
