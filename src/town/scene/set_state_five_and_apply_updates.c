#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern void set_script_flag_bit(s32);
extern void clear_script_flag_bit(s32);
extern s32 get_script_flag_mask(s32);
extern s32 scene_update_state;

/* Set state 5 and apply the two updates when check 0x145D succeeds. */
s32 set_state_five_and_apply_updates(void) {
    scene_update_state = 5;
    if (get_script_flag_mask(F_sero_end) != 0) {
        set_script_flag_bit(F_niko_selro_asa);
        clear_script_flag_bit(Fp_niko_kenkatyu);
        return 0;
    }
    return 1;
}
