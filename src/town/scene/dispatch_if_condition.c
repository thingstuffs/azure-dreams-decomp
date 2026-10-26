#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void set_indexed_entry_flag(s32 record, s32 entry_index);

/*
 * Sets the indexed entry flag and returns one only while F_s24_door_open has a nonzero script flag
 * mask.
 */
s32 dispatch_if_condition_1463(s32 dispatch_value, s32 dispatch_option) {
    if (get_script_flag_mask(F_s24_door_open) != 0) {
        set_indexed_entry_flag(dispatch_value, dispatch_option);
        return 1;
    }
    return 0;
}
