#include "shared/position_query.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

void initialize_scene_action_record();     /* extern */
void initialize_motion_action();     /* extern */
void initialize_actor_action_state();     /* extern */
M2C_UNK initialize_action_object();     /* extern */
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();                      /* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();               /* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();      /* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();                      /* extern */
s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41();                                /* extern */
extern u8 D_800CFCEF;


typedef struct S_800930E4_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800930E4_0;   /* target in update_actor_interaction_actions */

typedef struct S_800930E4_1 {
    u8 unk_00;
} S_800930E4_1;   /* &D_800CFCEF in update_actor_interaction_actions */

typedef struct S_800930E4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800930E4_2;   /* self in update_actor_interaction_actions */

typedef struct S_800930E4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800930E4_3;   /* state in update_actor_interaction_actions */

/* Updates the target and dispatches actions based on its value, a countdown, and state flags. */
void update_actor_interaction_actions(void *self_arg, void *target_arg, M2C_UNK context_arg) {
    void *self;
    M2C_UNK context;
    s16 target_value;
    u16 countdown;
    u16 busy_countdown;
    GameWork *state;

    context = context_arg;
    state = &g_game_work;

    handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile(target_arg);
    self = self_arg;

    move_both_components_toward_zero_direction_dependent_steps_clamping_zero(target_arg);
    if (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0) {
        target_value = select_the_smaller_position_query_result_capped_n_64_writes_associated(target_arg, ((u8 *)&D_800FE488));
        if ((target_value - ((S_800930E4_0 *)target_arg)->unk_0A) >= 4) {
            if (((S_800930E4_1 *)(&D_800CFCEF))->unk_00 == 0) {
                initialize_action_object(self, target_arg, context);
                return;
            }
        } else if (((S_800930E4_1 *)(&D_800CFCEF))->unk_00 == 0) {
            compute_and_clamps_vector_based_adjustment_updates_town(target_arg, target_value, ((u8 *)&D_800FE488));
        }
        countdown = ((S_800930E4_2 *)self)->unk_0A - 1;
        ((S_800930E4_2 *)self)->unk_0A = countdown;
        if ((s16) countdown >= 0) {
            if (state->buttons & 0xF000) {
                initialize_motion_action(self, target_arg, context);
                return;
            }
            if (((s32)state->unk_010) & 0x10) {
                initialize_actor_action_state(self, target_arg, context);
                return;
            }
            return;
        }
    } else {
        busy_countdown = ((S_800930E4_2 *)self)->unk_0A - 1;
        ((S_800930E4_2 *)self)->unk_0A = busy_countdown;
        if ((s16) busy_countdown >= 0) {
            return;
        }
    }
    initialize_scene_action_record(self, target_arg, context);
}
