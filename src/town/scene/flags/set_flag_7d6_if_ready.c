#include "script_symbols.h"
#include "town/scene/entry_flag_queries.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* Clear flags 0xFCB and 0xFCD; if 0x7D1 and 0xFD5 are set and 0x7D2 is clear, set flag 0x7D6 and return 1. */
s32 set_sbs24_pad04_if_ready(void)
{
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    if ((get_script_flag_mask(F_sbs24_top) != 0) &&
        (get_script_flag_mask(F_sbs24_pad00) == 0) &&
        (get_script_flag_mask(Fr_cheriru_pad28) != 0)) {
        set_script_flag_bit(F_sbs24_pad04);
        return 1;
    }
    return 0;
}
