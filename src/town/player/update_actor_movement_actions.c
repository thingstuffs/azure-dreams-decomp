#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town.h"
#include "town/player.h"
#include "town/player/object.h"

#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
#include "town/player/coordinates.h"
struct Rec_func_80094268_arg0; struct ObjectPosition; void initialize_actor_action_state(struct Rec_func_80094268_arg0 *, struct ObjectPosition *, s32);     /* extern */
void initialize_action_handler_with_count_six(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
struct Rec_D_800CFCB4; extern struct Rec_D_800CFCB4 town_actor_control;


typedef struct S_80092320_1 {
    u8 unk_00;
} S_80092320_1;   /* &D_800CFCEF in update_actor_movement_actions */


/* Update the actor and select an action from the reference value, state flags, and timer. */
void update_actor_movement_actions(Rec_func_80094268_arg0 *action, EntityRec *actor, s32 context) {
    GameWork *state = &g_game_work;
    s16 reference_value;
    s32 action_result;
    u16 ticks_left;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(actor);
    store_the_valid_shared_angle_in_offset_hex_10(action);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
    reference_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &position_query_scratch);
    if ((reference_value - actor->z.w.i) >= 4) {
        if (((S_80092320_1 *)(&town_action_state_flag))->unk_00 == 0) {
            initialize_action_object(action, actor, context);
            return;
        }
    } else if (((S_80092320_1 *)(&town_action_state_flag))->unk_00 == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), reference_value, (struct TownVec * *)(&position_query_scratch));
    }
    if ((state->pressed_buttons) & 0x10) {
        initialize_actor_action_state(action, (struct ObjectPosition *)(actor), context);
        return;
    }
    ticks_left = action->unk_0A.as_u16 - 1;
    action->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        initialize_action_object_and_play_sound((s32 * *)(action), (s32)(actor), context);
        return;
    }
    if ((state->pressed_buttons) & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(action, &town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(action, actor, context);
                return;
            }
            initialize_action_object_with_counter(action, actor, context);
            return;
        }
        if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action(action, actor, context);
            return;
        }
    } else if (select_an_available_entry_matching_direction_returns_status(&town_actor_control) <= 0) {
        initialize_action_handler_with_count_six(action, actor, context);
    }
    return;
}
