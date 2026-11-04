#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "shared/position_views.h"
#include "town/event/motion.h"

/* Clear status and values, then initialize the state's data pointer and mode. */
void initialize_target_motion_state(TownObjectRecord *state, Rec_D_800CFCB4 *status, MotionDeltaView *values, void *unused_extra_ptr) {
    status->unk_15 = 0;
    values->velocity_x = 0;
    values->velocity_y = 0;
    values->velocity_z = 0;
    state->unk_50.as_pm = &update_motion_toward_shared_target;
    state->timer.as_s16 = 7;
}
