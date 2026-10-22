/* Saves camera lock values and restores them through the town script state. */
/* inferred-strong G00575: camera_lock_return_g00575; joins CL:town/func_800A79AC,PD:town/engine:800D0C48; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A79AC, PD:town/engine:800D0C48. */
#include "town/map/camera_lock_return_g00575.h"

/* tcame_lock: Save and clear the two camera lock values. */
void tcame_lock(void) {
    s32 lock_value_0;
    s32 lock_value_1;

    lock_value_0 = town_camera_chase_state[9];
    lock_value_1 = town_camera_chase_state[10];
    town_camera_chase_state[9] = 0;
    town_camera_chase_state[10] = 0;
    saved_camera_callbacks[0] = lock_value_0;
    saved_camera_callbacks[1] = lock_value_1;
}

/* tcame_return: copy the saved camera values into script state slots 9 and 10. */
void tcame_return(void) {
    town_camera_chase_state[9] = saved_camera_callbacks[0];
    town_camera_chase_state[10] = saved_camera_callbacks[1];
}

/* tcame_return_plus: return the camera and clear its secondary state word. */
void tcame_return_plus(void) {
    s32 *camera_state = &town_camera_chase_state[0];

    tcame_return();

    *(s32 *)((s8 *)camera_state + 4) = 0;
}
