/* Saves camera lock values and restores them through the town script state. */
/* inferred-strong G00575: camera_lock_return_g00575; joins CL:town/func_800A79AC,PD:town/engine:800D0C48; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A79AC, PD:town/engine:800D0C48. */
#include "town/map/camera_lock_return_g00575.h"

/* tcame_lock: Save and clear the two camera lock values. */
void tcame_lock(void) {
    TownCameraCallback lock_value_0;
    TownCameraCallback lock_value_1;

    lock_value_0 = town_camera_chase_state.select_target;
    lock_value_1 = town_camera_chase_state.track_target;
    town_camera_chase_state.select_target = 0;
    town_camera_chase_state.track_target = 0;
    saved_camera_callbacks[0] = lock_value_0;
    saved_camera_callbacks[1] = lock_value_1;
}

/* tcame_return: copy the saved camera values into script state slots 9 and 10. */
void tcame_return(void) {
    town_camera_chase_state.select_target = saved_camera_callbacks[0];
    town_camera_chase_state.track_target = saved_camera_callbacks[1];
}

/* tcame_return_plus: return the camera and clear its secondary state word. */
void tcame_return_plus(void) {
    TownCameraState *camera_state = &town_camera_chase_state;

    tcame_return();

    camera_state->previous_target = 0;
}
