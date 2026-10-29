#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player/coordinates.h"
#include "town/player.h"
#include "town/player/position.h"


#ifndef NULL
#define NULL 0
#endif

extern void initialize_actor_action_state();
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);

extern void *town_target_record[3];

typedef struct S_80092698_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80092698_2;   /* D_800CFCC4[0] in update_actor_with_interaction_state */

/* Update the entity and dispatch its next action from the sampled value, countdown, and global state. */
void update_actor_with_interaction_state(Rec_func_80094268_arg0 *controller, EntityRec *entity, s32 context) {
    s16 sampled_value;
    u16 countdown;
    GameWork *state = &g_game_work;
    s32 *samples;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(entity);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(entity);
    samples = &position_query_scratch;
    sampled_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(entity, samples);
    if ((sampled_value - entity->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_object(controller, entity, context);
            return;
        }
    } else if (town_action_state_flag == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(entity, sampled_value, samples);
    }
    countdown = controller->unk_0A.as_u16 - 1;
    controller->unk_0A.as_u16 = countdown;
    if ((s16)countdown < 0) {
        if (town_target_record[0] != NULL) {
            if (((S_80092698_2 *)(town_target_record[0]))->unk_14 == 2) {
                initialize_scene_action_record(controller, entity, context);
                return;
            }
        }
        initialize_actor_movement_interaction_action(controller, entity, context);
        return;
    }
    if ((state->pressed_buttons) & 0x10) {
        initialize_actor_action_state(controller, entity, context);
    }
}
