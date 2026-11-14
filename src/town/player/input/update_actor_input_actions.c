#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "town/player/coordinates.h"
#include "engine/object.h"
#include "town/player.h"
#include "town/player/input.h"
#include "town/player/position.h"


extern void init_threshold_countdown_action(void *, void *,void *);
extern void initialize_actor_action_state(void *, void *, s32);
extern void initialize_action_object(void *, void *, s32);
extern void initialize_interaction_fallback_action(void *, void *,void *);
extern void initialize_action_object_with_counter(void *, ObjectPosition *, s32);
extern void initialize_actor_movement_interaction_action(void *, void *,void *);

extern s32 town_actor_control;

/* Update the entity and dispatch its handler according to state flags and checks. */
void update_actor_input_actions(void *context, ObjectPosition *entity, s32 update_arg)
{
    GameWork *state = &g_game_work;
    s16 reference_value;
    s32 state_flags;
    s32 check_result;

    resolve_collision_axis_order(entity);
    apply_velocity_friction(entity);
    reference_value = query_capped_surface_height(entity, &position_query_scratch);
    if ((reference_value - entity->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(context, entity, update_arg);
            return;
        }
    }
    else if (town_action_state_flag == 0) {
        set_height_and_slope_velocity(entity, reference_value, &position_query_scratch);
    }

    state_flags = (state->pressed_buttons);
    if (state_flags & 0x10) {
        initialize_actor_action_state(context, entity, update_arg);
        return;
    }
    if (state_flags & 0x40) {
        check_result = select_adjacent_source_entry(context, &town_actor_control);
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
            store_input_angle(context);
            if (select_entry_by_input_direction(&town_actor_control) > 0) {
                return;
            }
        }
        initialize_interaction_fallback_action(context, entity, update_arg);
    }

    return;
}
