#include "script_symbols.h"
#include "town/scene/entry_flag_queries.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* Checks event prerequisites and updates the corresponding event flags. */
s32 set_taiin_if_ready(void)
{
    if ((get_script_flag_mask(F_sbs24_top) != 0) &&
        (get_script_flag_mask(F_sbs24_pad00) == 0) &&
        (get_script_flag_mask(Fr_hospital_scene07_2) != 0) &&
        ((get_script_flag_mask(F_sbs16_top) == 0) ||
         (get_script_flag_mask(Ft_tai) != 0))) {
        set_script_flag_bit(F_taiin);
        return 1;
    }

    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    return 0;
}
