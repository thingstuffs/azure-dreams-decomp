#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "town/player/coordinates.h"
#include "town/event.h"
struct TownObj;
struct TownVec;

typedef struct {
    u8 pad0[0xA];
    u16 field_A;
} Obj800AD0E4;

extern void initialize_scene_action_record(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void initialize_motion_action(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void initialize_actor_action_state(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void initialize_action_object(Obj800AD0E4 *, Obj800AD0E4 *, s32);
extern void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(Obj800AD0E4 *);
extern void compute_and_clamps_vector_based_adjustment_updates_town(struct TownObj *obj, s32 base_value, struct TownVec **vec_ptr);

/* Update the object and dispatch actions based on its value, timer, and state flags. */
void update_object_and_dispatch_actions(Obj800AD0E4 *timer_obj, Obj800AD0E4 *object, s32 action_arg) {
    GameWork *state = &g_game_work;
    s16 next_value;
    u16 timer;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(object);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(object);
    next_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(object, &position_query_scratch);

    if ((next_value - (s16)object->field_A) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(timer_obj, object, action_arg);
            return;
        }
    } else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(object, next_value, &position_query_scratch);
    }

    timer = timer_obj->field_A - 1;
    timer_obj->field_A = timer;
    if ((s16)timer < 0) {
        initialize_scene_action_record(timer_obj, object, action_arg);
        return;
    }

    if (((u32)state->buttons) & 0xF000) {
        initialize_motion_action(timer_obj, object, action_arg);
        return;
    }

    if (((u32)state->pressed_buttons) & 0x10) {
        initialize_actor_action_state(timer_obj, object, action_arg);
        return;
    }

    update_positions_from_origin(object);
}
