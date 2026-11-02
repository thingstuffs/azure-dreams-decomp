#include "script_symbols.h"
#include "common.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* Reset two flags, set flag 0xFE4, and set flag 0x680 if flag 0x11FD is active. */
s32 reset_two_flags_flag_flag(void) {
    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    set_script_flag_bit(Ft_tai);
    if (get_script_flag_mask(Fp_cheriru_kangofu) != 0) {
        set_script_flag_bit(F_sbs16_pad06);
        return 1;
    }
    return 0;
}
