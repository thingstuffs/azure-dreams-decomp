#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* If flag 0xFB1 is set, set flag 0xFD3 and return 1; otherwise clear flags 0xFCB and 0xFCD and return 0. */
s32 set_flag_0xfd3_when_flag_0xfb1_set(void)
{
    if (get_script_flag_mask(Fr_hospital_naoruru) != 0) {
        set_script_flag_bit(F_chriru_mode_home);
        return 1;
    }
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    return 0;
}
