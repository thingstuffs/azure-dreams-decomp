#include "shared/position_query.h"
#include "common.h"

extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(void *object);
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(void *object);
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated(void *object, void *data);
extern void compute_and_clamps_vector_based_adjustment_updates_town(void *object, s16 value, void *data);
extern void initialize_action_object(void *state, void *object, s32 context);
extern void initialize_timed_scene_action(void *state, void *object, s32 context);

extern u8 D_800CFCEF[];

/* Update the object, check its target value, and advance the countdown. */
void update_threshold_countdown_action(void *state, void *object, s32 context) {
    s16 target_value;
    u16 countdown;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(object);
    target_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, ((u8 *)&D_800FE488));
    if (target_value - *(s16 *)((u8 *)object + 0xA) >= 4) {
        if (D_800CFCEF[0] == 0) {
            initialize_action_object(state, object, context);
            return;
        }
    } else {
        if (D_800CFCEF[0] == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town(object, target_value, ((u8 *)&D_800FE488));
        }
    }

    countdown = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = countdown;
    if ((s16)countdown < 0) {
        initialize_timed_scene_action(state, object, context);
    }
}
