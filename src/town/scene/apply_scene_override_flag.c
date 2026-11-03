#include "town/scene.h"
#include "modules/town_ovl_3ef1c8.h"
#include "town/player/state.h"

/* Reports the alternate gate only when it first sets the override flag. */
s32 apply_scene_override_flag(s32 unused_first, s32 unused_second) {
    if (get_script_flag_mask(0x79F) != 0) {
        return 0;
    }
    if (get_script_flag_mask(0x1391) != 0) {
        set_script_flag_bit(0x79F);
        return 0;
    }
    if (get_script_flag_mask(0x1389) != 0) {
        set_script_flag_bit(0x79F);
        return 1;
    }
    return 0;
}
