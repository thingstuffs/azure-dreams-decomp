#include "common.h"
#include "shared/position_views.h"
#include "town/player.h"
#include "town/player/motion.h"
#include "town/player/state.h"


extern u8 town_blocked_directions[9];

/* Clear motion along blocked directions and update the affected axes. */
void clear_blocked_motion(ObjectPosition *state)
{
    if (town_blocked_directions[2] != 0 && state->velocity_x < 0) {
        state->velocity_x = 0;
        copy_x_to_collision_motion(state);
    }

    if (town_blocked_directions[3] != 0 && state->velocity_x > 0) {
        state->velocity_x = 0;
        copy_x_to_collision_motion(state);
    }

    if (town_blocked_directions[4] != 0 && state->velocity_y < 0) {
        state->velocity_y = 0;
        sync_collision_motion_y(state);
    }

    if (town_blocked_directions[5] != 0 && state->velocity_y > 0) {
        state->velocity_y = 0;
        sync_collision_motion_y(state);
    }

    if (town_blocked_directions[1] != 0 && state->velocity_z > 0) {
        state->velocity_z = 0;
        copy_z_to_collision_motion(state);
    }

    if (town_blocked_directions[0] != 0 && state->velocity_z < 0) {
        state->velocity_z = 0;
        copy_z_to_collision_motion(state);
    }
}
