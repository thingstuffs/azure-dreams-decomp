#ifndef TOWN_PLAYER_PERIODIC_ACTION_EFFECT_G00533_H
#define TOWN_PLAYER_PERIODIC_ACTION_EFFECT_G00533_H
/* G00533: shared declarations for periodic action effect. */
/* Original-file evidence (G00533): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009408C. */

#include "common.h"
#include "shared/position_query.h"
#include "shared/town_action_flag.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "shared/sprite_frame_state.h"

typedef struct S_800917EC_2 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800917EC_2;

s32 scale_random_to_unsigned_halfword_limit();
void init_flagged_action_fallback(s32 **record, void *ptr, void *ptr2);
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void play_periodic_sound();
void store_the_valid_shared_angle_in_offset_hex_10();
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58();
void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides();
s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
void compute_and_clamps_vector_based_adjustment_updates_town();
void handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile();
void spawn_radial_effect_objects();
extern u8 D_800D043C[];
extern s32 D_800FE4E0;
extern u8 D_800D0158;

/* Functions defined in this translation unit. */
void update_actor_with_periodic_effect(Rec_func_80094268_arg0 *actor, EntityRec *position, s32 context);
void reset_action_handler_on_flag(s32 **handler_slot, s32 context, SpriteFlagsView *state);

#endif
