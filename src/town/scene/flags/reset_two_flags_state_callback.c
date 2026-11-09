#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/flags.h"
#include "town/player/state.h"

/* Reset two flags and invoke the state callback with 0x10 and 0x200. */
s32 reset_two_flags_state_callback(void) {
    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    town_scene_root->services->callback_2F8(0x10, 0x200);
    return 0;
}
