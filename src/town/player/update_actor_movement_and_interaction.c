#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_800CFCC4.h"
#include "town/player/coordinates.h"
#include "engine/script.h"
#include "town.h"
#include "town/event.h"
#include "town/player/state.h"
#include "town/shop.h"
#include "town/player/object.h"

void submit_object_resource_data();                         /* extern */
struct Rec_func_80094268_arg0; void initialize_actor_position_interaction_action(struct Rec_func_80094268_arg0 *, s32, s32);     /* extern */
struct ObjectPosition; void initialize_input_driven_scene_object(s32 * *, struct ObjectPosition *, s32);     /* extern */
void initialize_action_callback_from_entry(s32 **record, void *ptr, void *ptr2);
void initialize_busy_checked_countdown_action(Rec_func_80094268_arg0 *record,void *unused,void *setup_value);
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
void init_motion_action_callback(s32 record, s32 setup_value, s32 init_value);
#include "town/player/object/entity_record_fields.h"                      /* extern */
#include "town/player.h"
extern void D_80093B00();
extern void D_8009B828();
extern void actor_target_motion_address();
extern void town_owner_dispatch_address();
struct Rec_D_800CFCB4; extern struct Rec_D_800CFCB4 town_actor_control;
extern void *town_target_record;
extern s32 town_interaction_pending[];
extern s32 *town_player_action_callback;


typedef struct S_800927EC_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800927EC_4;

typedef struct S_800927EC_5 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800927EC_5;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_2C in update_actor_movement_and_interaction */

/* Update the actor and dispatch town movement and interaction input. */
void update_actor_movement_and_interaction(void *actor, EntityRec *position, s32 context) {
    GameWork *input = &g_game_work;
    S_800927EC_4 *interaction;
    s16 ground_height;
    s32 interaction_result;
    s32 target_handler;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(position);
    store_the_valid_shared_angle_in_offset_hex_10(actor);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(position);
    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(position, &position_query_scratch);
    if ((ground_height - position->z.w.i) >= 4) {
        if (town_action_state_flag == 0) {
            initialize_action_callback_from_entry(actor, position, context);
            return;
        }
    } else {
        if (town_action_state_flag == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(position), ground_height, (struct TownVec * *)(&position_query_scratch));
        }
    }
    if ((input->pressed_buttons) & 0x10) {
        initialize_input_driven_scene_object(actor, (struct ObjectPosition *)(position), context);
        return;
    }
    if ((input->pressed_buttons) & 0x80) {
        if ((town_target_record != NULL) && (((Rec_D_800CFCC4 *)town_target_record)->unk_14 == 4)) {
            run_the_three_update_routines_context((s32)(position));
            init_timed_dispatch_action(actor, position, context);
            town_interaction_pending[0] = 1;
            return;
        }
        clear_entity_record_fields(position);
        run_the_three_update_routines_context((s32)(position));
        if (run_the_action_sequence_context_unless_flag_hex_a_5_set((s32)(actor - 0x20)) != 0) {
            set_default_scene_data_pointer(actor, position, context);
            town_player_action_callback = &D_80093B00;
            return;
        }
    } else {
        if ((input->pressed_buttons) & 0x40) {
            initialize_busy_checked_countdown_action(actor, position, context);
            return;
        }
        if ((get_status_active_entry_matching_direction(&town_actor_control) == -1) && (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0)) {
            select_an_available_entry_matching_direction_returns_status(&town_actor_control);
            store_the_valid_shared_angle_in_offset_hex_10(actor);
            init_motion_action_callback(actor, position, context);
            target_handler = ((S_800927EC_5 *)(((Rec_func_80094268_arg0 *)actor)->unk_2C))->unk_50;
            if ((target_handler != &D_8009B828) && (target_handler != &actor_target_motion_address)) {
                if (target_handler != &town_owner_dispatch_address) {
                    ((Rec_func_80094268_arg0 *)actor)->unk_2C = NULL;
                }
            }
            interaction = (S_800927EC_4 *)&town_actor_control;
            interaction_result = select_response_for_source_and_target(interaction->unk_10,
                ((Rec_func_80094268_arg0 *)actor)->unk_2C);
            if (interaction_result != 0) {
                call_script(interaction_result);
            } else {
                submit_object_resource_data(interaction->unk_10);
            }
            town_player_action_callback = &D_80093B00;
            return;
        }
        if (input->buttons & 0xF000) {
            initialize_actor_position_interaction_action(actor, (s32)(position), context);
        }
    }
}
