#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"

s32 test_resident_bitmap_bit();                         /* extern */
void submit_object_resource_data();                         /* extern */
void initialize_motion_action();     /* extern */
M2C_UNK func_80094088();     /* extern */
void initialize_actor_action_state();     /* extern */
M2C_UNK initialize_action_object();     /* extern */
void func_800943B8();     /* extern */
M2C_UNK initialize_action_object_with_counter();     /* extern */
M2C_UNK initialize_actor_movement_interaction_action();     /* extern */
void store_the_valid_shared_angle_in_offset_hex_10();                      /* extern */
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();                      /* extern */
s32 select_an_available_entry_matching_direction_returns_status();            /* extern */
s32 select_an_eligible_source_entry_stores_pointer_in_destination();               /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                      /* extern */
void initialize_record_and_select_active_data();     /* extern */
extern s32 D_800CFCB4;
extern M2C_UNK D_800CFCEF;


typedef struct S_80090A74_1 {
    u8 unk_00;
} S_80090A74_1;   /* &D_800CFCEF in dispatch_actor_interaction_actions */

typedef struct S_80090A74_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80090A74_2;


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
    u8 *height_data;
    u8 *shared_data;
    GameWork *input_state = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(record);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(record);
    {
        void *height_record = record;

        height_data = ((u8 *)&D_800FE488);
        height = select_the_smaller_position_query_result_capped_n_64_writes_associated(height_record, height_data);
    }
    if ((height - record->z.w.i) >= 4) {
        if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
            initialize_action_object(actor, record, context);
            return;
        }
    } else if (((S_80090A74_1 *)(&D_800CFCEF))->unk_00 == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town(record, height, height_data);
    }
    if (((s32)input_state->unk_010) & 0x10) {
        initialize_actor_action_state(actor, record, context);
        return;
    }
    if (((s32)input_state->unk_010) & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(actor, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(actor, record, context);
                return;
            }
            initialize_action_object_with_counter(actor, record, context);
            return;
        }
        if (test_resident_bitmap_bit(0xA4) != 0) {
            func_80094088(actor, record, context);
            return;
        }
    } else {
        shared_data = (u8 *)&D_800CFCB4;
        interaction_result = select_an_available_entry_matching_direction_returns_status(shared_data);
        if (interaction_result != 0) {
            if (interaction_result == -1) {
                store_the_valid_shared_angle_in_offset_hex_10(actor);
                initialize_record_and_select_active_data(actor, record, context);
                actor->unk_2C = 0;
                submit_object_resource_data(((S_80090A74_4 *)shared_data)->unk_10);
                return;
            }
            func_800943B8(actor, record, context);
            return;
        }
        page_base = (u8 *)(u32)(input_state->buttons & 0xF000);
        if (page_base != 0) {
            initialize_motion_action(actor, record, context);
        }
    }
}
