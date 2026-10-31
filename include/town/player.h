#ifndef TOWN_PLAYER_H
#define TOWN_PLAYER_H

#include "common.h"


struct Rec_func_80094268_arg0;
struct S_800935BC_0;
struct SpriteFrameState;
void approach_target_tile_until_timeout(struct Rec_func_80094268_arg0 *target, struct S_800935BC_0 *position, void *transition_arg);

/* get_linked_record_field.c */
s32 get_linked_record_field_2_d_60(void);

struct S_8009A18C_0;
struct S_8009A18C_1;

void tick_player_countdown(void *object, void *state);
void initialize_player_data_reference(struct S_8009A18C_0 *data_ref, struct S_8009A18C_1 *state);

/* Phase-specific names of the existing linked-value and flag helpers. */
s32 get_entry_linked_value(void);
s32 read_entry_linked_value(void);
s32 get_scene_script_flag_mask(s32 flag);
void set_scene_script_flag_bit(s32 flag);
void clear_scene_script_flag_bit(s32 flag);






void set_default_scene_data_pointer(s32 **out_ptr, void *unused_position, s32 unused_context);

void initialize_threshold_interaction_action(void *record, void *unused_entity, s32 unused_context);

/* Callback entry points. */
s32 draw_entry_overlays(void);
s32 read_and_clear_stored_value(void);
s32 store_value_and_get_masked_offset(s32 unused_0, s32 unused_1, s32 unused_2, s32 stored_value);
void dispatch_deferred_callback(s32 callback_first_value, s32 callback_second_value, s32 callback_third_value, s32 unused_value);
void dispatch_state_callback_by_mode(s32 value, void *ptr, void *ptr2, s32 unused);
void forward_player_state_update(void *object, s32 value_1, s32 value_2);
void forward_value_context_data_mode(s32 value, void *context, void *data, s32 mode);
void no_op_scene_callback_b(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/entity.h"
void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);

#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_func_8009431C_arg0.h"
#include "shared/position_views.h"
struct TownObj;
struct TownVec;
void apply_fixed_point_boundary_corrections_according_global_800_fe_5_cc(s32 *value);
void clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(s32 *source);
void clear_slot_n_3_copies_slot_n_0(s32 *value);
void compute_and_clamps_vector_based_adjustment_updates_town(struct TownObj *obj, s32 base_value, struct TownVec **vec_ptr);
void correct_fixed_point_value_at_boundaries(s32 *value);
void dispatch_actor_interaction_actions(Rec_func_8009431C_arg0 *actor, EntityRec *record, s32 context);
s32 get_status_active_entry_matching_direction(void *entries);
void initialize_record_with_handler_and_countdown_800(Rec_func_80094268_arg0 *record, s32 setup_value, struct SpriteFrameState *init_context);
void initialize_scene_action_record(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);
void initialize_timed_scene_action(Rec_func_80094268_arg0 *record, s32 unused, struct SpriteFrameState *setup_value);
void move_both_components_toward_zero_direction_dependent_steps_clamping_zero(EntityRec *record);
void noop_player_scene_action(void);
void run_the_three_update_routines_context(void *context);
s32 select_an_available_entry_matching_direction_returns_status(void *record);
s32 select_an_eligible_source_entry_stores_pointer_in_destination(void *destination, void *source);
void set_player_travel_timing(void *actor, void *motion, s32 context);
void store_the_valid_shared_angle_in_offset_hex_10(void *record);
void tick_countdown_and_initialize_target(UnsignedCountdownView *state, s32 value);
void update_falling_actor_and_handle_ground(s32 context, EntityRec *actor, s32 action_arg);
void update_threshold_and_interaction(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context);
void update_threshold_timed_action(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context);

#include "shared/dungeon_moving_views.h"
struct S_80097AD0_1;
void spawn_radial_objects(MovingPosition *origin, struct S_80097AD0_1 *spread, s32 count);

void initialize_record_and_select_active_data(s32 record, s32 setup_value, s32 init_value);

struct S_800980B4_0;
void call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(s32 context);
void tick_countdown_and_reset_value(struct S_800980B4_0 *state, s32 value, s32 mode);

s16 call_callee_8008_c_4_c_8_global_800_d_0410_parameter(s32 input_value, s32 parameter);
void call_the_callee_80096208_callee_800962_b_8(s32 input_value);
void call_the_callee_800962_b_8_callee_80096208(s32 input_value);
void dispatch_actor_action(void *actor, void *position, void *context);
void play_periodic_sound(s32 count, s32 interval);

void clear_global_80110_ec_0_global_80082_a_39(void);
s32 push_point_to_containing_edges(s32 *x, s32 *y);

s32 sum_enabled_record_weights(void);

void apply_global_scene_value(s32 value);
void initialize_town_context_action(void);

s32 step_angle_12_toward(s32 angle_delta, s32 target_angle, s32 step);

void apply_pending_indexed_value(s32 index, s32 value);
void apply_pending_table_entry(s32 index, s32 entryValue);

#include "shared/vector.h"
void apply_the_enabled_movement_offsets_adding_z_offset_only_positive(IntVector3 *out);
void copy_current_record_components_3(void *output);
void dispatch_parameterized_or_default(s32 handler_param);
void initialize_shared_scene_data(s32 **out_ptr);
u32 view_relative_angle_sector(s32 angle);

#endif
