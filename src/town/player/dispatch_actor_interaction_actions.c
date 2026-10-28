#include "script_symbols.h"
#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"

#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
#include "town/player/coordinates.h"
void submit_object_resource_data();                         /* extern */
struct Rec_func_80094268_arg0; void initialize_motion_action(struct Rec_func_80094268_arg0 *, s32, s32);     /* extern */
#include "records/Rec_func_80094268_arg0.h"
void init_threshold_countdown_action(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);     /* extern */
struct Rec_func_80094268_arg0; struct ObjectPosition; void initialize_actor_action_state(struct Rec_func_80094268_arg0 *, struct ObjectPosition *, s32);     /* extern */
void initialize_action_object(s32 **record, void *ptr, void *ptr2);     /* extern */
struct Rec_func_80094268_arg0; void init_movement_action(struct Rec_func_80094268_arg0 *, s32, s32);     /* extern */
void initialize_action_object_with_counter(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);     /* extern */
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);     /* extern */
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
s32 select_an_available_entry_matching_direction_returns_status(void *);            /* extern */
s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *, void *);               /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
void initialize_record_and_select_active_data(s32, s32, s32);     /* extern */
extern s32 town_actor_control;


typedef struct S_80090A74_1 {
    u8 unk_00;
} S_80090A74_1;   /* &D_800CFCEF in dispatch_actor_interaction_actions */


typedef struct S_80090A74_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80090A74_4;

/* Update the actor and dispatch town actions from input and interaction state. */
void dispatch_actor_interaction_actions(Rec_func_8009431C_arg0 *actor, EntityRec *record, s32 context) {
    s16 height;
    s32 action_result;
    s32 interaction_result;
    u8 *page_base;
    s32 *height_data;
    S_80090A74_4 *shared_data;
    GameWork *input_state = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(record);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(record);
    {
        void *height_record = record;

        height_data = &position_query_scratch;
        height = select_the_smaller_position_query_result_capped_n_64_writes_associated(height_record, height_data);
    }
    if ((height - record->z.w.i) >= 4) {
        if (((S_80090A74_1 *)(&town_action_state_flag))->unk_00 == 0) {
            initialize_action_object(actor, record, context);
            return;
        }
    } else if (((S_80090A74_1 *)(&town_action_state_flag))->unk_00 == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(record), height, (struct TownVec * *)(height_data));
    }
    if ((input_state->pressed_buttons) & 0x10) {
        initialize_actor_action_state((struct Rec_func_80094268_arg0 *)(actor), (struct ObjectPosition *)(record), context);
        return;
    }
    if ((input_state->pressed_buttons) & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(actor, &town_actor_control);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(actor, record, context);
                return;
            }
            initialize_action_object_with_counter(actor, record, context);
            return;
        }
        if (test_resident_bitmap_bit(F_t_attack_enable) != 0) {
            init_threshold_countdown_action(actor, record, context);
            return;
        }
    } else {
        shared_data = (S_80090A74_4 *)&town_actor_control;
        interaction_result = select_an_available_entry_matching_direction_returns_status(shared_data);
        if (interaction_result != 0) {
            if (interaction_result == -1) {
                store_the_valid_shared_angle_in_offset_hex_10(actor);
                initialize_record_and_select_active_data((s32)(actor), (s32)(record), context);
                actor->unk_2C = 0;
                submit_object_resource_data(shared_data->unk_10);
                return;
            }
            init_movement_action((struct Rec_func_80094268_arg0 *)(actor), (s32)(record), context);
            return;
        }
        page_base = (u8 *)(u32)(input_state->buttons & 0xF000);
        if (page_base != 0) {
            initialize_motion_action((struct Rec_func_80094268_arg0 *)(actor), (s32)(record), context);
        }
    }
}
