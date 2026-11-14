#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* Clear flags 0xFCB and 0xFCD; if 0x7D1 and 0xFD6 are set and 0x7D2 is clear, set flag 0x7D7 and return 1. */
s32 set_sbs24_pad05_if_ready(void)
{
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    if ((get_script_flag_mask(F_sbs24_top) != 0) &&
        (get_script_flag_mask(F_sbs24_pad00) == 0) &&
        (get_script_flag_mask(Fr_cheriru_pad29) != 0)) {
        set_script_flag_bit(F_sbs24_pad05);
        return 1;
    }
    return 0;
}
