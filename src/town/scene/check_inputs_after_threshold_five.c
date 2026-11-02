#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

/* Query 0x146C, process it, and return the saved query result. */
s32 check_inputs_after_threshold_five(void) {
    s32 query_result;

    query_result = get_script_flag_mask(F_mama_ret_first);
    set_script_flag_bit(F_mama_ret_first);
    return query_result;
}
