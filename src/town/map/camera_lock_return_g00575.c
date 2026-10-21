/* inferred-strong G00575: camera_lock_return_g00575; joins CL:town/func_800A79AC,PD:town/engine:800D0C48; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A79AC, PD:town/engine:800D0C48. */
#include "town/map/camera_lock_return_g00575.h"

/* tcame_lock: Save and clear the two camera lock values. */
void tcame_lock(void) {
    s32 lock_value_0;
    s32 lock_value_1;

    lock_value_0 = D_80100DE0[9];
    lock_value_1 = D_80100DE0[10];
    D_80100DE0[9] = 0;
    D_80100DE0[10] = 0;
    D_800D0C48[0] = lock_value_0;
    D_800D0C48[1] = lock_value_1;
}

/* tcame_return: copy the saved camera values into script state slots 9 and 10. */
void tcame_return(void) {
    D_80100DE0[9] = D_800D0C48[0];
    D_80100DE0[10] = D_800D0C48[1];
}

/* tcame_return_plus: return the camera and clear its secondary state word. */
void tcame_return_plus(void) {
    s32 *camera_state = &D_80100DE0[0];

    tcame_return();

    *(s32 *)((s8 *)camera_state + 4) = 0;
}
