#ifndef TOWN_PLAYER_H
#define TOWN_PLAYER_H
struct SpriteFrameState;

#include "common.h"


struct S_800935BC_0;
struct TownObjectRecord;
void approach_target_tile_until_timeout(struct TownObjectRecord *target, struct S_800935BC_0 *position, void *transition_arg);

/* get_linked_record_field.c */
s32 get_town_state_count(void);

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






void set_no_op_scene_handler(s32 **out_ptr, void *unused_position, s32 unused_context);

void initialize_threshold_interaction_action(void *record, void *unused_entity, s32 unused_context);

/* Callback entry points. */
s32 draw_entry_overlays(void);
s32 read_and_clear_stored_value(void);
s32 store_pending_value_and_get_source(s32 unused_0, s32 unused_1, struct SpriteFrameState *unused_2, s32 stored_value);
void dispatch_deferred_callback(s32 callback_first_value, s32 callback_second_value, s32 callback_third_value, s32 unused_value);
void dispatch_state_callback_by_mode(s32 value, void *ptr, void *ptr2, s32 unused);
void forward_player_state_update(void *object, s32 value_1, struct SpriteFrameState *value_2);
void forward_state_callback_dispatch(s32 value, void *context, void *data, s32 mode);
void no_op_scene_callback_b(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/entity.h"
/* Position and other record callers share this signed word at +0x14. */
void add_vertical_gravity(void *record_arg);

#include "shared/town_object.h"
#include "records/Rec_func_8009431C_arg0.h"
#include "shared/position_views.h"
struct TownObj;
struct TownVec;
void clamp_x_to_probe_bounds(ObjectPosition *value);
void copy_z_to_collision_motion(ObjectPosition *source);
void copy_x_to_collision_motion(ObjectPosition *value);
void set_height_and_slope_velocity(ObjectPosition *obj, s32 base_value, struct TownVec **vec_ptr);
void correct_fixed_point_value_at_boundaries(ObjectPosition *value);
s32 get_status_active_entry_matching_direction(void *entries);
void init_approach_record(TownObjectRecord *record, ObjectPosition *setup_value, struct SpriteFrameState *init_context);
void initialize_scene_action_record(TownObjectRecord *record, void *ptr, void *ptr2);
void initialize_timed_scene_action(TownObjectRecord *record, ObjectPosition *unused, struct SpriteFrameState *setup_value);
void apply_velocity_friction(ObjectPosition *record);
void noop_player_scene_action(void);
void sync_collision_motion_xyz(ObjectPosition *context);
s32 select_entry_by_input_direction(void *record);
s32 select_adjacent_source_entry(void *destination, void *source);
void store_input_angle(void *record_arg);
void tick_countdown_and_initialize_target(UnsignedCountdownView *state, ObjectPosition *value);
#include "shared/sprite_frame_state.h"
void update_airborne_object_with_land_timer(TownObjectRecord *state, ObjectPosition *entity, SpriteFrameState *context);
void update_ground_timed_action(TownObjectRecord *state, ObjectPosition *entity, struct SpriteFrameState *context);

#include "shared/dungeon_moving_views.h"
struct S_80097AD0_1;
void spawn_radial_objects(MovingPosition *origin, struct S_80097AD0_1 *spread, s32 count);


void accelerate_toward_input_angle(ObjectPosition *context);

s16 evaluate_primary_probe_samples(s32 input_value, s32 parameter);
void clamp_x_then_correct_boundaries(ObjectPosition *input_value);
void correct_boundaries_then_clamp_x(ObjectPosition *input_value);
void begin_town_actor_interaction(void *actor, void *position, void *context);
void play_periodic_sound(s32 count, s32 interval);

void clear_action_globals(void);
s32 push_point_to_containing_edges(s32 *x, s32 *y);

s32 sum_enabled_record_weights(void);

void apply_global_scene_value(void *value);
void initialize_town_context_action(void);

s32 step_angle_toward(s32 angle_delta, s32 target_angle, s32 step);

void apply_pending_indexed_value(s32 index, s32 value);
void apply_pending_table_entry(s32 index, s32 entryValue);

#include "shared/vector.h"
#include "town/player/record.h"
void apply_actor_control_offsets(ObjectPosition *out);
void copy_scene_payload_position(void *output);
void dispatch_parameterized_or_default(s32 handler_param);
u32 view_relative_angle_sector(s32 angle);


void begin_countdown_advance_cursor_action(TownObjectRecord *object, ObjectPosition *setup_parameter, struct SpriteFrameState *sprite);

s32 record_value_table_contains(s32 target_value);
void complete_player_action(void *actor_arg, ObjectPosition *motionState, struct SpriteFrameState *sprite);


void step_x_toward_fixed_target(TownObjectRecord *context, ObjectPosition *record, struct SpriteFrameState *sprite);

void run_player_indexed_handler(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite);

void set_player_travel_timing(void *actor, ObjectPosition *motion, struct SpriteFrameState *sprite);

void tick_countdown_and_reset_value(TownPlayerRecord *state, ObjectPosition *value, struct SpriteFrameState *sprite);

void update_falling_actor_and_handle_ground(TownObjectRecord *context, ObjectPosition *actor, struct SpriteFrameState *sprite);

void initialize_record_with_update_parameters(TownObjectRecord *record, ObjectPosition *update_value, struct SpriteFrameState *sprite);

void dispatch_actor_interaction_actions(Rec_func_8009431C_arg0 *actor, ObjectPosition *record, struct SpriteFrameState *sprite);


void update_actor_interaction_actions(void *self_arg, ObjectPosition *target_arg, SpriteFrameState *sprite);

void run_action_with_idle_fallback(s32 *value, ObjectPosition *state, struct SpriteFrameState *sprite);

struct S_80090F00_0;

void update_countdown_and_fallback(struct S_80090F00_0 *object, ObjectPosition *context, struct SpriteFrameState *sprite);

struct S_80097D2C_0;
void dispatch_fallback_request(TownObjectRecord *request, void *request_data, void *request_param, s32 check_param);
void invoke_object_state_callback(struct S_80097D2C_0 *object, void *position, void *sprite);

void initialize_record_and_select_active_data(void *record, ObjectPosition *position, SpriteFrameState *sprite);
void initialize_shared_scene_data(s32 **out_ptr, void *unused_position, struct SpriteFrameState *unused_sprite);
void accelerate_toward_angle_capped(s16 angle, s32 max_length, ObjectPosition *vector);
void update_actor_movement_and_interaction(void *actor, ObjectPosition *position, s32 context);
void update_ground_countdown_unless_busy(void *state, ObjectPosition *object, s32 context);

#endif
