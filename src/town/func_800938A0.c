#include "shared/position_query.h"
#include "common.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"

void initialize_actor_action_state();        /* extern */
void initialize_action_object();        /* extern */
void store_the_valid_shared_angle_in_offset_hex_10();                         /* extern */
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();                      /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                      /* extern */


typedef struct S_80091000_1 {
    u8 unk_00;
} S_80091000_1;   /* &D_800CFCEF in update_actor_ground_and_input */

typedef struct S_80091000_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091000_2;   /* state in update_actor_ground_and_input */

/* Update the actor against ground height, then dispatch input actions. */
void update_actor_ground_and_input(s32 controller, EntityRec *actor, s32 context) {
    s16 ground_height;
    GameWork *input_state = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(actor);
    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(actor);
    ground_height = select_the_smaller_position_query_result_capped_n_64_writes_associated(actor, &D_800FE488);
    if ((ground_height - actor->z.w.i) >= 4) {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            initialize_action_object(controller, actor, context);
            return;
        }
    } else {
        if (((S_80091000_1 *)(&D_800CFCEF))->unk_00 == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town(actor, ground_height, &D_800FE488);
        }
    }
    if (((s32)input_state->unk_010) & 0x10) {
        initialize_actor_action_state(controller, actor, context);
        return;
    }
    if (input_state->buttons & 0xF000) {
        store_the_valid_shared_angle_in_offset_hex_10(controller);
    }
}
