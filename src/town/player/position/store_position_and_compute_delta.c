#include "town/player/position.h"

// Store the new three-component value and its difference from the previous value.
void store_position_and_compute_delta(s32 *newValue)
{
    town_collision_motion.velocity_x = newValue[0] - town_collision_motion.x.v;
    town_collision_motion.velocity_y = newValue[1] - town_collision_motion.y.v;
    town_collision_motion.velocity_z = newValue[2] - town_collision_motion.z.v;
    town_collision_motion.x.v = newValue[0];
    town_collision_motion.y.v = newValue[1];
    town_collision_motion.z.v = newValue[2];
}
