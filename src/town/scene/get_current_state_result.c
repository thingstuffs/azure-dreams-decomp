#include "script_symbols.h"
#include "common.h"

extern s32 scene_update_state[3];

extern s32 func_800175B0(void);
extern s32 func_800198D0(s32 condition_id);
extern s32 func_80019A8C(void);

/*
 * Clears scene_update_state and accepts the egg flag without the Niko love flag, or the secondary
 * check with a value of at least 20.
 */
s32 get_current_state_result(void) {
    scene_update_state[0] = 0;

    if ((func_800198D0(F_selfy_get_tamago) != 0) &&
        (func_800198D0(Ft_niko_love) == 0)) {
        return 1;
    }

    if ((func_800175B0() != 0) && (func_80019A8C() >= 20)) {
        return 1;
    }

    return 0;
}
