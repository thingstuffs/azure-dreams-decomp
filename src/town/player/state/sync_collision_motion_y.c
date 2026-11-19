#include "common.h"
#include "town/player/position.h"
#include "shared/entity.h"
#include "town/player/state.h"

/* Copy the Y position and clear the previous Y step. */
void sync_collision_motion_y(ObjectPosition *source) {
    town_collision_motion.velocity_y = 0;
    town_collision_motion.y.v = source->y.v;
}
