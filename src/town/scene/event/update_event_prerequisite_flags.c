#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "town/player/state.h"

/* Checks event prerequisites and updates the corresponding event flags. */
s32 update_event_prerequisite_flags(void)
{
    if ((get_script_flag_mask(F_sbs24_top) != 0) &&
        (get_script_flag_mask(F_sbs24_pad00) == 0) &&
        (get_script_flag_mask(Fr_hospital_scene04) != 0) &&
        ((get_script_flag_mask(F_sbs16_top) == 0) ||
         (get_script_flag_mask(Ft_nyu) != 0))) {
        set_script_flag_bit(F_sbs24_pad08);
        return 1;
    }

    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    return 0;
}
