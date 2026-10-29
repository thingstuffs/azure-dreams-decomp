#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/position_views.h"
#include "town/player/coordinates.h"
#include "town.h"
#include "town/player.h"
#include "town/player/motion.h"
#include "town/player/position.h"
#include "town/player/state.h"
#include "town/shop.h"

   /* target in update_actor_interaction_actions */

typedef struct S_800930E4_1 {
    u8 unk_00;
} S_800930E4_1;   /* &D_800CFCEF in update_actor_interaction_actions */

   /* self in update_actor_interaction_actions */


/* Updates the target and dispatches actions based on its value, a countdown, and state flags. */
void update_actor_interaction_actions(void *self_arg, SignedHeightView *target_arg, s32 context_arg) {
    UnsignedCountdownView *self;
    s32 context;
    s16 target_value;
    u16 countdown;
    u16 busy_countdown;
    GameWork *state;

    context = context_arg;
    state = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(target_arg);
    self = self_arg;

    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(target_arg);
    if (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0) {
        target_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(target_arg, &position_query_scratch);
        if ((target_value - target_arg->z) >= 4) {
            if (((S_800930E4_1 *)(&town_action_state_flag))->unk_00 == 0) {
                initialize_action_object(self, target_arg, context);
                return;
            }
        } else if (((S_800930E4_1 *)(&town_action_state_flag))->unk_00 == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town(target_arg, target_value, &position_query_scratch);
        }
        countdown = self->unk_0A - 1;
        self->unk_0A = countdown;
        if ((s16) countdown >= 0) {
            if (state->buttons & 0xF000) {
                initialize_motion_action(self, target_arg, context);
                return;
            }
            if ((state->pressed_buttons) & 0x10) {
                initialize_actor_action_state(self, target_arg, context);
                return;
            }
            return;
        }
    } else {
        busy_countdown = self->unk_0A - 1;
        self->unk_0A = busy_countdown;
        if ((s16) busy_countdown >= 0) {
            return;
        }
    }
    initialize_scene_action_record(self, target_arg, context);
}
