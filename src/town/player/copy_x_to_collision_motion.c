#include "common.h"
#include "town/player/position.h"
#include "shared/entity.h"
#include "town/player.h"

/* Copy the X position and clear the previous X step. */
void copy_x_to_collision_motion(ObjectPosition *position) {
    town_collision_motion.velocity_x = 0;
    town_collision_motion.x.v = position->x.v;
}
