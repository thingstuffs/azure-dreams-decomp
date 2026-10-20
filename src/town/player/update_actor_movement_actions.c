#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"

#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
void func_80094088(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);
struct Rec_func_80094268_arg0; struct S_800942B0_0; void initialize_actor_action_state(struct Rec_func_80094268_arg0 *, struct S_800942B0_0 *, s32);     /* extern */
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void initialize_action_object_and_play_sound(s32 * *, s32, s32);     /* extern */
void initialize_action_handler_with_count_six(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);
void initialize_action_object_with_counter(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);
void initialize_actor_movement_interaction_action(s32 **record, void *ptr, void *ptr2);
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"                      /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
s32 select_an_available_entry_matching_direction_returns_status(void *);            /* extern */
s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *, void *);               /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
extern M2C_UNK D_800CFCB4;


typedef struct S_80092320_1 {
    u8 unk_00;
} S_80092320_1;   /* &D_800CFCEF in update_actor_movement_actions */

typedef struct S_80092320_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092320_2;   /* state in update_actor_movement_actions */


/* Update the actor and select an action from the reference value, state flags, and timer. */
void update_actor_movement_actions(Rec_func_80094268_arg0 *action, EntityRec *actor, s32 context) {
    GameWork *state = &g_game_work;
    s16 reference_value;
    s32 action_result;
    u16 ticks_left;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(actor);
    store_the_valid_shared_angle_in_offset_hex_10(action);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
    reference_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &D_800FE488);
    if ((reference_value - actor->z.w.i) >= 4) {
        if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
            initialize_action_object(action, actor, context);
            return;
        }
    } else if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
        compute_and_clamps_vector_based_adjustment_updates_town((struct TownObj *)(actor), reference_value, (struct TownVec * *)(&D_800FE488));
    }
    if (((s32)state->unk_010) & 0x10) {
        initialize_actor_action_state(action, (struct S_800942B0_0 *)(actor), context);
        return;
    }
    ticks_left = action->unk_0A.as_u16 - 1;
    action->unk_0A.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        initialize_action_object_and_play_sound((s32 * *)(action), (s32)(actor), context);
        return;
    }
    if (((s32)state->unk_010) & 0x40) {
        action_result = select_an_eligible_source_entry_stores_pointer_in_destination(action, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                initialize_actor_movement_interaction_action(action, actor, context);
                return;
            }
            initialize_action_object_with_counter(action, actor, context);
            return;
        }
        if (test_resident_bitmap_bit(0xA4) != 0) {
            func_80094088(action, actor, context);
            return;
        }
    } else if (select_an_available_entry_matching_direction_returns_status(&D_800CFCB4) <= 0) {
        initialize_action_handler_with_count_six(action, actor, context);
    }
    return;
}
