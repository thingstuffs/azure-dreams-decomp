#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Process 0xFB7 and 0xFB8, then return whether the 0xFC0 check succeeds. */
s32 reset_hospital_flags_and_check_scene03(void) {
    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    return get_script_flag_mask(Fr_cheriru_scene03) != 0;
}
