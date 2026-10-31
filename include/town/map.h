#ifndef TOWN_MAP_H
#define TOWN_MAP_H
/* Prototypes of the functions defined in src/town/map/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_800A0668_arg0.h"
#include "shared/dungeon_delay_views.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_pointees.h"
#include "shared/vector.h"
#include "town/map/animation.h"

struct Func800AB788Arg;
struct Func800BFE50Object;
struct GameWork;
struct S_8008B9D8_0;
struct S_8008BA00_0;
struct S_800A08F0_0;
struct S_800A092C_0;
struct S_800A0958_0;
struct S_800A0C30_0;
struct S_800A0C30_1;
struct S_800A0CC0_0;
struct S_800A0DAC_0;
struct S_800A0E3C_1;
struct S_800A3B80_3;
struct S_800A51CC_0;
struct S_800A526C_1;
struct S_800A878C_2;
struct S_800A895C_1;
struct S_800BC764_0;
struct S_800BDE7C_0;
struct S_800C21F8_0;
struct S_func_800A0708_0;
struct ScratchQuad;
struct SpriteFrameState;
struct TownCameraState;
struct TownMapSpawnState;
struct TownStripScratch;

/* adjust_record_fields.c */
void adjust_record_fields(s32 unused, void *record);

/* advance_building_texture_and_palette.c */
void advance_building_texture_and_palette(BuildingSelectionHandlerBody *state, s32 unused, s32 upload_arg);

/* advance_town_map_countdown_callback.c */
void advance_town_map_countdown_callback(struct S_8008BA00_0 *state, void *position, void *sprite);

/* akichi_vivian_chk.c */
u8 akichi_vivian_chk(void);

/* apply_and_store_setting.c */
void apply_and_store_setting(IntVector3 *setting);

/* apply_building_pending_updates.c */
void apply_building_pending_updates(void);

/* blit_indexed_origin_block.c */
void blit_indexed_origin_u16_block(s32 dst_x, s32 dst_y, s32 image_id, void *dst);

/* blit_origin_block.c */
void blit_origin_u16_block(s32 dst_x, s32 dst_y, u16 *src, void *dst);

/* build_current_event_entry_list.c */
void build_current_event_entry_list(void);

/* build_land_building.c */
void BuildLandBuilding(s32 slot, s16 palette);

/* build_map_variant_entry_list.c */
void build_map_variant_entry_list(void);

/* building_grid_g00638.c */
void clear_halfword_grid_128(s16 *grid);
void update_active_building_entries(void);
void clear_and_initialize_building_grid(s32 grid);

/* came_bright_set.c */
void came_bright_set(u32 brightness);

/* camera_lock_return_g00575.c */
void tcame_lock(void);
void tcame_return(void);
void tcame_return_plus(void);

/* check_build_building_land.c */
s32 CheckBuildBuildingLand(s32 record_key);

/* check_fixed_value_pairs.c */
s32 check_fixed_value_pairs(void);

/* check_scratch_quad_half_turn_gaps.c */
s32 check_scratch_quad_half_turn_gaps(struct ScratchQuad *scratch);

/* clear_first_record_field_and_counter.c */
void clear_first_record_field_and_counter(void);

/* clear_global_halfword_grid.c */
void clear_global_halfword_grid_128(void);

/* clear_selected_entry_at_bottom_center.c */
void clear_selected_entry_at_bottom_center(void);

/* clear_transition_word.c */
void clear_transition_word(void);

/* copy_low_halfword_coordinates.c */
void copy_low_halfword_coordinates(u16 *destination, const u16 *source);

/* copy_record_tail_bytes.c */
void copy_record_tail_bytes(void);

/* copy_variant_building_tiles.c */
void copy_variant_building_tiles(s16 x, s16 y, u16 *src_tiles);

/* decrease_town_record_value.c */
void decrease_town_record_value(void **record_ref);

/* decrease_town_record_value_by_two_hundred.c */
void decrease_town_record_value_by_two_hundred(void **record_ref);

/* directional_sprite_effect_g00644.c */
s32 create_directional_sprite_effect(void *position, s16 angle);
void advance_coordinates_and_propagate_flags(void *object_data, ObjectPosition *motion, SpriteFrameState *status);
void wait_then_process_record(struct S_800BC764_0 *context, void *unused, SpriteFrameState *record);
void initialize_record_resources(void *record, void *init_context, SpriteFrameState *resource_target);

/* display_fade_g00643.c */
struct TimedColorFadeObject;
struct BuildTwoDisplayEntriesBody;
void advance_color_fade_and_set_completion(struct TimedColorFadeObject *fade_state, s32 unused, SpriteFrameState *visual);
void advance_timed_state_and_set_completion(struct BuildTwoDisplayEntriesBody *object);
void build_two_display_entries(void *data_id, s32 position_offset);

/* door.c */
s32 check_door_status_inverted(void *object);
void initialize_door_variant(void *record_data, void *position, struct SpriteFrameState *unused_sprite);
void handle_door_check_result(struct S_func_800A0708_0 *object, void *callback_arg, s32 callback_data);
void install_next_door_handler(void *object, void *unused_context, void *update_context, s32 unused_data);
void open_door_to_target(void *object, void *context);
void door_no_op(void);
void advance_door_open_angle(struct S_800A08F0_0 *door);
void tick_door_open_countdown(struct S_800A092C_0 *state);
void advance_door_close_angle(struct S_800A0958_0 *door);
void *find_door_keyed_node(s32 requested_value);
void door_open_demo_set_sub(s32 door_id, s16 demo_angle);
void door_open_demo_set(s32 script_context);
void door_atari_on_off(s32 door_id, s16 collision_enabled);
void into_dn_door_demo_set(void);
void trigger_door_interaction_effect(void *actor, void *target, void *position);
void change_door_map(void *map_source, s32 *map_table);
void advance_door_step(void *entity, void *unused_context, void *update_context, s32 unused_data);
void select_tower_entry_handler_by_item_count(struct S_800A0C30_0 *script_state, void *unused_context, struct S_800A0C30_1 *event_params);
void set_door_handler_if_ready(struct S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3);
void update_door_completion_state(u8 *object, s32 unused, s32 state_id, s32 state_arg);
void advance_door_state_counter(struct S_800A0DAC_0 *state, s32 unused, s32 context_a, s32 context_b);
void tick_door_countdown(Rec_func_800A0668_arg0 *object, struct S_800A0E3C_1 *source, s32 update_arg_a, s32 update_arg_b);
void into_dn_door_jobs(void);
s32 check_door_input_and_angle(Rec_func_800A0668_arg0 *object, void *test_value);

/* dot_sign_with_truncated_q_coefficients.c */
s32 dot_sign_with_truncated_q_12_coefficients(s32 recordTableAddress, s32 recordIndexOrCoefficient, s32 componentsOrSum);

/* draw_randomized_white_points.c */
s32 draw_randomized_white_points(void *first_object, void *first_coords);

/* draw_shaded_quad_ring.c */
void draw_shaded_quad_ring(s32 shape, s32 source);

/* event_fountain_chk.c */
u8 event_fountain_chk(void);

/* fade_timed_primitive.c */
void fade_timed_primitive(void *record_fields, void *unused, SpriteFrameState *primitive);

/* fill_wrapped_four_by_four_grid.c */
void fill_wrapped_four_by_four_grid(s32 start_x, s16 start_y, s32 unused_value);

/* find_sound_entry_or_terminator_index.c */
s32 find_sound_entry_or_terminator_index(s32 target_value);

/* flagged_tile_scan_g00593.c */
void append_valid_key_pair(s32 first_value, s32 second_value, u32 unused_cell);
s32 count_flagged_cells_in_opposite_directions(s32 dir, s16 start_x, s16 start_y);
s32 count_flagged_tiles_along_direction(s16 direction, s16 start_x, s16 start_y);
void clear_flagged_cells_and_reset_list(void);
void refresh_state_and_dispatch_angles(void);

/* forward_surface_query_with_argument_g01117.c */
s16 forward_surface_query_with_argument(SignedPositionView *record, void **plane_out);
s16 forward_highest_surface_query(SignedPositionView *record);
s16 forward_smallest_surface_x_query(SignedPositionView *record);
s16 evaluate_surface_components_a(SignedPositionView *components);
s16 evaluate_surface_components_b(SignedPositionView *components);
s16 evaluate_surface_components_c(SignedPositionView *components);
void update_map_world_extents(void);
s32 find_min_qualifying_plane_height(u32 query_x, u32 query_y, s16 query_height, void **plane_out);
s32 find_highest_surface_within_range(s32 world_x, s32 world_y, s16 height);
s16 find_smallest_surface_x_across_tiles(s32 query_x, s32 query_y, s32 query_z);
s32 find_highest_valid_cell_height(s32 world_x, s32 world_z, s32 world_y);

/* grid_base.c */
void blit_nonzero_u16_block_to_grid(s16 dst_x, s16 dst_y, u16 *src);

/* handle_town_map_input.c */
void handle_town_map_input(u8 *object, void *transform, void *context);

/* increase_town_record_value.c */
void increase_town_record_value(void **record_ref);

/* init_line_colors.c */
s32 draw_depth_sorted_gradient_lines(TownMapFallingObject *node);

/* initialize_building_graphics.c */
void initialize_building_graphics(void);

/* initialize_building_region_resources.c */
void initialize_building_region_resources(void);

/* initialize_building_scene_objects.c */
void initialize_building_scene_objects(s32 draw_param);

/* initialize_building_selection_handler.c */
void initialize_building_selection_handler(void);

/* initialize_building_shared_buffer.c */
void initialize_building_shared_buffer(void);

/* initialize_control_block.c */
void initialize_control_block(struct TownCameraState *control);

/* initialize_record_with_defaults.c */
void initialize_record_with_defaults(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);

/* interpolate_view_components.c */
void interpolate_view_components(struct S_800A526C_1 *transition);

/* map_cursor_input_g00641.c */
void store_state_and_update_tile_center(s32 state);
void update_wrapping_indices_and_input(void);

/* mark_populated_building_entities.c */
void mark_populated_building_entities(void);

/* mark_referenced_building_records.c */
void mark_referenced_building_records(void);

/* midpoint_tracking_g00574.c */
void restart_or_update_midpoint_tracking(struct TownCameraState *state);
void reset_or_advance_target_midpoint(struct TownCameraState *state);

/* min_indexed_query.c */
s16 min_indexed_query(s32 context, void *data, s32 count);

/* no_op_building_callback.c */
void no_op_building_callback(struct GameWork *work, s32 size, s32 limit);

/* no_op_catalog_callback.c */
void no_op_catalog_callback(void);

/* no_op_entry_callback.c */
void no_op_entry_callback(void);

/* no_op_map_callback.c */
void no_op_map_callback(void);

/* object_callback_tables_g00653.c */
void initialize_object_and_replace_callbacks(void);
void invoke_callbacks_until_terminator(void);

/* p_came_rotset.c */
void p_came_rotset(s32 rotation);

/* p_came_set.c */
void p_came_set(s32 position);

/* paired_actor_motion_g00645.c */
void update_randomized_actor_movement(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, s32 update_mode);
void initialize_object_and_dispatch_by_state(struct Func800BFE50Object *object, s32 *params, void *dispatch_context);
void randomize_paired_object_motion(void *pair);
s32 event_tori_in(void *source);

/* process_enabled_entries.c */
void load_and_apply_town_building_tiles(void);

/* process_linked_record_values.c */
s32 process_linked_record_values(void *object, s32 x, s32 initial_value);

/* queue_adjacent_shaded_quads.c */
void queue_adjacent_shaded_quads(struct Func800AB788Arg *strip);

/* radial_motion_effect_g00586.c */
void *create_reverse_motion_effect(struct S_800A878C_2 *source_motion, u32 flags);
void spawn_radial_effect_objects(MovingPosition *center, struct S_800A895C_1 *spread, s32 count);

/* randomized_position_effect_g00585.c */
void *create_randomized_position_effect(MovingPosition *source_position);
void build_randomized_offset_records(void *origin, void *spread, s32 count);

/* range_group_checks_g00652.c */
s32 find_containing_range_group(s32 value, s16 **range_groups);
s32 pass_value_and_range_groups(s32 value);
s32 check_masked_value_in_current_range(s32 value);

/* release_town_map_record.c */
void release_town_map_record(void *record_ref);

/* replace_active_table_callbacks.c */
void replace_active_table_callbacks(void *entry_data, void *unused_position, struct SpriteFrameState *unused_sprite);

/* request_event_with_toggled_map_bit.c */
void request_event_with_toggled_map_bit(void);

/* request_event_with_toggled_selector.c */
void request_event_with_toggled_selector(void);

/* restore_town_map_input_state.c */
void restore_town_map_input_state(void *object);

/* retry_sound_sequence_when_ready.c */
void retry_sound_sequence_when_ready(void);

/* run_callbacks_unless_suppressed.c */
void run_callbacks_unless_suppressed(void *object, void *check_data);

/* run_dual_context_callbacks.c */
void run_dual_context_callbacks(void);

/* run_object_callback_b.c */
void run_map_object_callback(struct S_8008B9D8_0 *object, void *position, void *sprite);

/* scene_below.c */
void initialize_building_scene_assets(void);

/* set_fallback_record_handler.c */
void set_fallback_record_handler(void *record);

/* set_record_handler_below_threshold.c */
void set_record_handler_below_threshold(void *record);

/* set_record_pointer_and_byte.c */
void set_record_pointer_and_byte(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);

/* shaded_tile_rendering_g00594.c */
void set_texture_quad_32_uv(u16 texture_page, u16 palette, u8 texture_u, u8 texture_v);
void render_shaded_map_tiles(void);
void draw_empty_map_cell_quads(u32 packet_limit);

/* sound_selection_g00648.c */
void copy_selected_sound_pair(void *output);
s16 *build_four_value_entry_result(s32 unused, s32 index);
void load_pending_sound_record(void);
void apply_sound_selections_and_update(void);

/* sound_sequence_load_g00649.c */
s32 tw_sd_sq_ld_call_sub(s32 sequence_id, s32 load_id, s32 load_flags);
void tw_sd_sq_ld_call(s32 effect_id, s32 effect_flags);

/* sound_sequence_replay_g00650.c */
s32 town_sd_sq_callagain_sub(s32 sequence_flags);
s32 town_sd_sq_callagain(void);

/* State stored in the body of a burst-particle spawner node. */
typedef struct BurstParticleSpawnerObject {
    /* 0x00 */ u8 pad_00[0x48];
    /* 0x48 */ u16 timer;
    /* 0x4A */ u8 pad_4A[2];
    /* 0x4C */ union { s16 s; u16 u; } state;
} BurstParticleSpawnerObject;

/* spawn_burst_particles_around_origin.c */
void spawn_burst_particles_around_origin(BurstParticleSpawnerObject *self, ObjectPosition *origin);

/* spawn_randomized_timed_objects.c */
void spawn_randomized_timed_objects(struct TownMapSpawnState *source);

/* store_normalized_building_code.c */
void store_normalized_building_code(s32 code);

/* switch_callback_beyond_distance_limit.c */
s32 switch_callback_beyond_distance_limit(struct S_800C21F8_0 *object);

/* target_interpolation_g00573.c */
void reset_or_copy_state_values(struct TownCameraState *state);
void restart_or_advance_target_interpolation(struct TownCameraState *state);

/* tcame_chase_fix.c */
void tcame_chase_fix(IntVector3 *target);

/* tcame_chase_fix_reset.c */
void tcame_chase_fix_reset(void);

/* tcame_chase_set.c */
void tcame_chase_set(void);

/* tcame_chase_tgt_reset.c */
void tcame_chase_tgt_reset(void);

/* tcame_set.c */
void tcame_chase2_set(void);

/* textured_resource_strips_g00571.c */
s32 process_linked_state_chain(void *initial_state, s32 carrier1, u8 *carrier2);
s32 emit_bidirectional_angular_segments(struct S_800A3B80_3 *object, s32 unused, void *context);
void *project_visible_textured_strips(void *origin, void *render_flags, struct TownStripScratch *draw_state, void *prim_buffer, u16 texture_index);
void create_resource_display_object(s16 resource_index);

/* town_map_mod_yorozu_item.c */
void town_map_mod_yorozu_item(s16 *tile_data, s16 object_type, s32 spawn_value);

/* town_map_set_g01113.c */
s32 town_map_set(s32 value_7c, s32 value_78);
s32 town_map_del(void);
s32 clear_town_map_status(void);
void initialize_town_map_object_state(s32 type_id, s32 *init_value_ptr, void *object, void *context);

/* town_rain_in.c */
void town_rain_in(s16 x, s16 y);

/* town_sd_se_callagain.c */
s32 town_sd_se_callagain(void);

/* trigger_action_and_finish_record.c */
void trigger_action_and_finish_record(u16 *record);

/* tw_sd_se_ld_call.c */
s32 tw_sd_se_ld_call(s32 sound_id, s32 sequence_id);

/* tw_seq_end_chk.c */
s32 tw_seq_end_chk(void);

/* update_angle_driven_offset.c */
void update_angle_driven_offset(void *object, DelayMotionZ *offset_state);

/* update_current_and_saved_coordinates.c */
void update_current_and_saved_coordinates(struct S_800A51CC_0 *object);

/* update_random_idle_wander.c */
void update_random_idle_wander(void *actor, void *motion, SpriteFrameState *sprite, s32 update_context);

/* update_record_output_grid.c */
void update_record_output_grid(struct S_800BDE7C_0 *record, s32 unused_value, TownGridOutputView *output, s32 unused_value2);

/* update_view_gray_level.c */
void update_view_gray_level(void);

#endif
