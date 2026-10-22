#ifndef TOWN_PLAYER_GROUND_INPUT_FALLBACK_G00532_H
#define TOWN_PLAYER_GROUND_INPUT_FALLBACK_G00532_H
/* G00532: shared declarations for ground input fallback. */
/* Original-file evidence (G00532): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800938A0. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/position_query.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"

/* extern */
typedef struct S_80091000_1 {
    u8 unk_00;
} S_80091000_1;

/* &D_800CFCEF in update_actor_ground_and_input */
typedef struct S_80091000_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_80091000_2;

/* state in update_and_fallback_on_input */
typedef struct S_80091114_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80091114_1;

void initialize_actor_action_state();
/* extern */
void initialize_action_object();
/* extern */
void store_the_valid_shared_angle_in_offset_hex_10();
/* extern */
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero();
/* extern */
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
/* extern */
void compute_and_clamps_vector_based_adjustment_updates_town();
/* extern */
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
extern void init_input_action_fallback(void *, void *, s32);

extern void initialize_scene_action_record(Rec_func_80094268_arg0 *, void *, void *);

/* Functions defined in this translation unit. */
void update_actor_ground_and_input(s32 controller, EntityRec *actor, s32 context);
void update_and_fallback_on_input(s32 *value, S_80091114_1 *context, s32 update_arg);
void update_input_and_fallback_action(s32 *value, s32 input_a, s32 input_b);

#endif
