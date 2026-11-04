#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player.h"
#include "town/player/state.h"

extern s32 scene_update_state[3];

/*
 * Clears scene_update_state and accepts the egg flag without the Niko love flag, or the secondary
 * check with a value of at least 20.
 */
s32 get_current_state_result(void) {
    scene_update_state[0] = 0;

    if ((get_script_flag_mask(F_selfy_get_tamago) != 0) &&
        (get_script_flag_mask(Ft_niko_love) == 0)) {
        return 1;
    }

    if ((count_enabled_town_entries() != 0) && (get_linked_record_field_2_d_60() >= 20)) {
        return 1;
    }

    return 0;
}
