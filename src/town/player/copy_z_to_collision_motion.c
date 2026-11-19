#include "common.h"
#include "town/player/position.h"
#include "shared/entity.h"
#include "town/player.h"

/* Copy the height and clear the previous vertical step. */
void copy_z_to_collision_motion(ObjectPosition *source) {
    town_collision_motion.velocity_z = 0;
    town_collision_motion.z.v = source->z.v;
}
