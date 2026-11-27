#include "town/scene/collision.h"
#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_8009B828_arg0.h"
#include "shared/position_views.h"
#include "town/event/motion.h"

/* Clear status and values, then initialize the state's data pointer and mode. */
void initialize_target_motion_state(TownObjectRecord *state, struct ColliderView *status, ObjectPosition *values, struct SpriteFrameState *unused_sprite) {
    status->enabled = 0;
    values->velocity_x = 0;
    values->velocity_y = 0;
    values->velocity_z = 0;
    state->state_callback.as_pm = &update_motion_toward_shared_target;
    state->timer = 7;
}
