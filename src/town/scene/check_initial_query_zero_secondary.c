#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"

// Updates event flags based on three prerequisite checks and reports whether they passed.
s32 check_initial_query_zero_secondary(void)
{
    if (get_script_flag_mask(F_sbs24_top) != 0 &&
        get_script_flag_mask(F_sbs24_pad00) == 0 &&
        get_script_flag_mask(F_cheriru_scene01) != 0) {
        set_script_flag_bit(F_sbs24_pad06);
        return 1;
    }

    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    return 0;
}
