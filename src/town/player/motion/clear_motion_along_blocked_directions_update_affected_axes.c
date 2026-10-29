#include "common.h"
#include "shared/position_views.h"
#include "town/player.h"
#include "town/player/motion.h"
#include "town/player/state.h"


extern u8 town_blocked_directions[9];

/* Clear motion along blocked directions and update the affected axes. */
void clear_motion_along_blocked_directions_update_affected_axes(MotionDeltaView *state)
{
    if (town_blocked_directions[2] != 0 && state->velocity_x < 0) {
        state->velocity_x = 0;
        clear_slot_n_3_copies_slot_n_0(state);
    }

    if (town_blocked_directions[3] != 0 && state->velocity_x > 0) {
        state->velocity_x = 0;
        clear_slot_n_3_copies_slot_n_0(state);
    }

    if (town_blocked_directions[4] != 0 && state->velocity_y < 0) {
        state->velocity_y = 0;
        clear_the_global_state_s_fifth_word_copy_source_s_second(state);
    }

    if (town_blocked_directions[5] != 0 && state->velocity_y > 0) {
        state->velocity_y = 0;
        clear_the_global_state_s_fifth_word_copy_source_s_second(state);
    }

    if (town_blocked_directions[1] != 0 && state->velocity_z > 0) {
        state->velocity_z = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(state);
    }

    if (town_blocked_directions[0] != 0 && state->velocity_z < 0) {
        state->velocity_z = 0;
        clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(state);
    }
}
