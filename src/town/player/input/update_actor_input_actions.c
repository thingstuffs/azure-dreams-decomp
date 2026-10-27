#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "town/player/coordinates.h"


#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 test_resident_bitmap_bit(s32);
extern void init_threshold_countdown_action(void *, void *,void *);
extern void initialize_actor_action_state(void *, void *, s32);
extern void initialize_action_object(void *, void *, s32);
extern void initialize_action_handler_with_count_six(void *, void *,void *);
extern void initialize_action_object_with_counter(void *, void *, s32);
extern void initialize_actor_movement_interaction_action(void *, void *,void *);
extern void store_the_valid_shared_angle_in_offset_hex_10(void *);
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(void *);
extern s32 select_an_available_entry_matching_direction_returns_status(void *);
extern s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *, void *);
extern void compute_and_clamps_vector_based_adjustment_updates_town(void *, s16, void *);
extern void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(void *);

extern s32 town_actor_control;

/* Update the entity and dispatch its handler according to state flags and checks. */
void update_actor_input_actions(void *context, EntityRec *entity, s32 update_arg)
{
    GameWork *state = &g_game_work;
    s16 reference_value;
    s32 state_flags;
    s32 check_result;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    reference_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(entity, &position_query_scratch);
    if ((reference_value - entity->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(context, entity, update_arg);
            return;
        }
    }
    else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(entity, reference_value, &position_query_scratch);
    }

    state_flags = (state->pressed_buttons);
    if (state_flags & 0x10) {
        initialize_actor_action_state(context, entity, update_arg);
        return;
    }
    if (state_flags & 0x40) {
        check_result = select_an_eligible_source_entry_stores_pointer_in_destination(context, &town_actor_control);
        if (check_result != 0) {
            if (check_result == 2) {
                initialize_actor_movement_interaction_action(context, entity, update_arg);
                return;
            }
            initialize_action_object_with_counter(context, entity, update_arg);
            return;
        }
        if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action(context, entity, update_arg);
            return;
        }
    }
    else {
        if (state->buttons & 0xF000) {
            store_the_valid_shared_angle_in_offset_hex_10(context);
            if (select_an_available_entry_matching_direction_returns_status(&town_actor_control) > 0) {
                return;
            }
        }
        initialize_action_handler_with_count_six(context, entity, update_arg);
    }

    return;
}
