#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* Reset two flags and set flag 0x67C when the prerequisite flags allow it. */
s32 reset_two_flags_flag_prerequisite(void) {
    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    if (get_script_flag_mask(F_sbs16_top) == 0) {
        return 0;
    }
    if (get_script_flag_mask(F_sbs16_pad00) != 0) {
        return 0;
    }
    set_script_flag_bit(F_sbs16_pad02);
    return 1;
}
