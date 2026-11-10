#include "script_symbols.h"
#include "common.h"

s32 set_script_flag_bit();                         /* extern */

/* Calls initialize_state_two_entries_pointer with ID 0x98F and returns its result. */
s32 select_data_array_based_flag(void) {
    return set_script_flag_bit(F_sbs34_pad15);
}
