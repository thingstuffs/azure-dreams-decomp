#ifndef TOWN_PLAYER_EFFECT_INITIALIZE_EFFECT_AND_ADJUST_VALUE_G01140_H
#define TOWN_PLAYER_EFFECT_INITIALIZE_EFFECT_AND_ADJUST_VALUE_G01140_H

struct ObjectPosition;
/* Initialize effect and adjust value. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01140 - CL:town/func_800A7E6C, CL:town/func_800A8134. */

#include "common.h"
#include "town/scene/collision.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_D_800FE490.h"
#include "shared/game_work.h"
#include "shared/position_query.h"
#include "shared/entity_objects.h"
/* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"                      /* extern */
/* extern */
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"                 /* extern */
/* extern */
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"      /* extern */
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"                      /* extern */
#include "town/player/move_both_components_toward_zero_direction_dependent_steps_clamping_zero_api.h"
#include "town/player/clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2_api.h"
#include "town/player/compute_and_clamps_vector_based_adjustment_updates_town_api.h"
#include "town/player/position/handle_resolves_movement_collisions_along_one_axis_using_boundary_probes_tile_api.h"
#include "shared/town_action_flag.h"
#include "town/player/store_the_valid_shared_angle_in_offset_hex_10_api.h"

typedef struct S_800A55CC_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A55CC_0_pre;

/* extern */
struct IntVector3;

/* extern */
struct Rec_D_800FE490;

typedef struct S_800A5638_0_pre {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_800A5638_0_pre;

typedef struct S_800A58CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A58CC_0;

/* (void *) shared_s0 in update_object_view_transition */
typedef struct S_800A58CC_2 {
    void * unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
} S_800A58CC_2;

struct EntityRec;

typedef struct {
    void *callback;
    u8 pad04[4];
    u16 mode;
    u16 timer;
    u8 pad0C[4];
    u16 direction;
} State;

typedef struct {
    u8 pad00[10];
    s16 height;
    s32 x;
    s32 y;
    s32 value;
} Actor;

typedef struct S_800A5DF8_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800A5DF8_0;

typedef struct S_800A5DF8_1 {
    u8 unk_00;
} S_800A5DF8_1;

/* &D_800CFCEF in update_actor_effect_transition */
typedef struct S_800A5DF8_4 {
    void * unk_00;
    u8 pad_04[0x4];
    s16 unk_08;
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5DF8_4;

typedef struct S_800A5FDC_0 {
    s32 unk_00;
    u8 pad_04[0x6];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_800A5FDC_0;

/* the 0x10 bytes before arg0 in initialize_effect_and_adjust_value, addressed as arg0[-1] */
extern void register_node_if_unregistered(void *object, void *setup_data);
void initialize_actor_action_state(void *object, EntityRec *state, s32 initData);
extern u8 player_motion_draw_address[];
extern s32 D_800D0CC0[];
/* extern */
void process_scene_record_update(void *,struct ObjectPosition *, void *);
/* extern */
void add_motion_deltas_to_position(ObjectPosition *motion);
void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(struct IntVector3 *);
/* extern */
void store_position_and_compute_delta(s32 *);
void update_the_s_field_10_using_callee_8008_fe_90(struct Rec_D_800FE490 *);
/* extern */
s32 update_object_and_clear_status_fields();
extern Rec_D_800CFCB4 town_actor_control;
extern Rec_D_800FE490 town_motion_list;
extern s32 D_800A5A98;
extern s16 town_scene_effect_flips[];
extern u8 town_position_reference_state[];
#include "engine/texture.h"
extern void step_actor_animation(void *, s32);
extern s32 view_relative_angle_sector(s16);
extern void clear_motion_along_blocked_directions_update_affected_axes(void *);
extern void copy_entity_record_fields(void *, void *);
/* arg0 in update_object_view_transition */
s32 read_map_cell_at_world_position(s16, s16);
/* extern */
s32 check_masked_value_in_current_range(s32);
extern u8 D_800D0000[];
extern int abs(int);
extern u8 D_800A5DF8;
extern u32 scale_random_to_unsigned_halfword_limit(s32 limit);
s32 runtime_estimate_vector_length(s32, s32);
extern short SD_Call(int flags);
extern void add_a_directional_step_vector_scale_down_exceeds_length_limit();
void spawn_directional_effects(void *, s32);
/* extern */
extern u8 D_800A5FDC[];
extern s32 input_angle_with_offset(s32 unused, s32 angle_offset);
extern s32 map_view_transition_address;

/* Shared import declarations; data casts preserve each measured view. */
extern u8 D_800903FC[];
extern s16 step_angle_12_toward(s32, s32, s32);
extern void add_hex_20000_s_signed_offset_hex_14(); /* Unprototyped: one or two arguments; retail reads only the first. */
extern s16 select_the_smaller_position_query_result_capped_n_64_writes_associated();
extern u8 town_blocked_directions[];
extern u8 town_movement_speed[];

/* Functions defined in this translation unit. */
void initialize_effect_and_adjust_value(void *object, EntityRec *record, s32 init_value);
void update_effect_record_and_dispatch(void *handler, ObjectPosition *record, s32 context);
void turn_entity_toward_target(void *entity, void *transform, void *sprite);
s32 compute_height_based_offset(EntityRec *state);
void update_object_view_transition(S_800A58CC_2 *state_arg, void *object);
void update_actor_movement_and_actions(State *state, Actor *actor);
void update_actor_effect_transition(S_800A5DF8_4 *state, S_800A5DF8_0 *actor, s32 context);
void update_town_movement_and_actions(u8 *state, EntityRec *table, void *action_context);

#endif
