#include "script_symbols.h"
#include "common.h"
#include "town/scene/state_data.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Set state 4 and return whether check 0x3FE fails or check 0x3FF succeeds. */
s32 set_state_four_and_check_conditions(void) {
    s32 result;
    s32 ret;

    scene_update_state = 4;
    if (get_script_flag_mask(F_sbs01_pad09) != 0) {
        result = get_script_flag_mask(F_sbs01_pad10);
        ret = 0;
        if (result == 0) {
            return ret;
        }
    }
    ret = 1;

    return ret;
}

/* MECHANISM: The post-call ret local supplies $zero in the branch delay slot and avoids an s-reg. */
