#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "town/player/coordinates.h"

extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(void *object);
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(void *object);
extern void compute_and_clamps_vector_based_adjustment_updates_town(void *object, s16 value, void *data);
extern void initialize_action_object(void *state, void *object, s32 context);
extern void initialize_actor_interaction_state_19(void *state, void *object, s32 context);
extern s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(void);


/* Update the object, handle its value threshold, and advance the countdown. */
void update_threshold_countdown_with_busy_check(void *state, void *object, s32 context) {
    s16 target_value;
    u16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(object);
    if (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0) {
        target_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch);
        if (target_value - *(s16 *)((u8 *)object + 0xA) >= 4) {
            if (town_action_state_flag == 0) {
                initialize_action_object(state, object, context);
                return;
            }
        } else {
            if (town_action_state_flag == 0) {
                compute_and_clamps_vector_based_adjustment_updates_town(object, target_value, &position_query_scratch);
            }
        }
    }

    countdown = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = countdown;
    if ((s16)countdown < 0) {
        initialize_actor_interaction_state_19(state, object, context);
    }
}
