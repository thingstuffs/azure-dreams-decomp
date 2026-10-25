#include "common.h"

extern s32 func_800175B0(void);
extern s32 func_80019A8C(void);
extern s32 scene_update_state;

/* Set state 1 and return whether the initial check passes and the count is at least 20. */
s32 set_state_one_and_check_count(void) {
    scene_update_state = 1;
    if (func_800175B0() != 0) {
        if (func_80019A8C() >= 20) {
            return 1;
        }
    }
    return 0;
}
