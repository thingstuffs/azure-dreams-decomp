#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H
/* Prototypes of the functions defined in src/engine/scene/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/vector.h"
#include "shared/object_node.h"

/* Two contiguous draw/packet contexts, each 0x108D4 bytes long. */
extern u8 upper_draw_context[2 * 0x108D4];

struct SpriteFrameState;
struct S_8003DF0C;
struct S_80041E28_Dst;
struct S_80041E28_Src;
struct S_800422DC_Other;
struct S_800422DC_Self;
struct S_80043FD0;
struct SpriteAttachment;
struct S_800510A0;
struct S_80051164;
struct Task;

/* build_entity_slot_snapshot.c */
void build_entity_slot_snapshot(struct S_800422DC_Self *snapshot, struct S_800422DC_Other *source);

/* change_map_by_home_rank.c */
void change_map_by_home_rank(void);

/* change_map_by_home_rank_secondary.c */
void change_map_by_home_rank_secondary(void);

/* change_map_by_home_rank_tertiary.c */
void change_map_by_home_rank_tertiary(void);

/* chg_map_second_house_sel.c */
void chg_map_second_house_sel(void);

/* create_callback_pair_payload.c */
/* Allocation wrappers forward a third value which this routine ignores. */
void *create_callback_pair_payload(void *second_value, void *first_value, unsigned long unused_value);

/* create_deferred_resource_transition_task.c */
struct Task *create_deferred_resource_transition_task(s16 mode, s16 lookup_id, void *(*handler)(void *), void *context);

/* entry_create_animated_selection_menu.c */
void *create_gauge_with_selection_menu(s32 context);

/* entry_find_target_byte_index_in_list.c */
void clear_selected_scene_entry_flags(void);

/* entry_itm_mon_koyaw_set.c */
void refresh_monster_items_from_creature_records(void);

/* file_load_com.c */
void file_load_com(void *packed_data);

/* find_last_flagged_record_by_id.c */
struct S_8003DF0C *find_last_flagged_record_by_id(struct S_8003DF0C *entry, s32 want, u16 *idx_out);

/* has_enough_available_runtime_nodes.c */
s32 has_enough_available_runtime_nodes(s32 limit);

/* init_double_buffered_gpu_environments.c */
void init_double_buffered_gpu_environments(void);

/* initialize_hardware_and_game_state.c */
void initialize_hardware_and_game_state(void);

/* initialize_runtime_table_defaults.c */
void initialize_runtime_table_defaults(void);

/* inline_fn.c */
inline s32 inline_fn(s32 value);
void *initialize_scene_object_in_buffer(s32 flags_or_addr, void *buffer, s16 word_count);

/* load_and_open_monster_status_display.c */
void load_and_open_monster_status_display(s32 first_arg, s32 second_arg, s32 third_arg, s32 fourth_arg, s32 fifth_arg);

/* load_indexed_resource_package.c */
int load_indexed_resource_package(short table_index);

/* load_resource_and_mirror_palette.c */
s32 load_resource_and_mirror_palette(s32 elem_index, s32 array_index);

/* load_scene_record.c */
void *load_scene_record(void *data);

/* load_scene_resource_group.c */
void load_scene_resource_group(s16 entry_index);

/* load_shared_resource_once.c */
void load_shared_resource_once(void);

/* mark_active_nodes_by_callback.c */
void mark_active_nodes_by_callback(s32 target_id);

/* play_scene_movie.c */
void play_scene_movie(void);

/* queue_entity_resource_descriptor_pair.c */
void queue_entity_resource_descriptor_pair(s32 first_value, s32 second_value, s16 callback_id);

/* queue_mode_selected_resource_table.c */
void queue_mode_selected_resource_table(void);

/* read_combined_controller_buttons.c */
s32 read_combined_controller_buttons(s32 unused_mode);

/* remove_marked_active_nodes.c */
void remove_marked_active_nodes(void);

/* render_object_scene_frame.c */
void render_object_scene_frame(void);

/* render_scene_frame_with_timing.c */
void render_scene_frame_with_timing(void);

/* reserve_runtime_slot.c */
s16 reserve_runtime_slot(s16 slot_id, s16 slot_value);

/* reset_game_state_preserving_session_fields.c */
void reset_game_state_preserving_session_fields(void);

/* reset_runtime_slot_state.c */
void reset_runtime_slot_state(void);

/* resolve_record_orientation_or_fallback.c */
struct SpriteAttachment *func_8003DE58(struct SpriteAttachment *records, struct SpriteFrameState *actor, GteShortVector *out_vec, s16 record_id);
struct SpriteAttachment *resolve_record_orientation_or_fallback(struct SpriteAttachment *records, struct SpriteFrameState *actor, GteShortVector *out_vec, s16 record_id);

/* restore_actor_stats_from_snapshot.c */
void restore_actor_stats_from_snapshot(struct S_80041E28_Dst *dst, struct S_80041E28_Src *src);

/* run_deferred_callbacks.c */
void run_deferred_callbacks(void *head);

/* runtime_load_packed_resource_chunks.c */
void runtime_load_packed_resource_chunks(s16 entry_id, u8 *stream);

/* runtime_reset_object_pool.c */
void runtime_reset_object_pool(void);

/* scene_begin_transition_data_read.c */
void scene_begin_transition_data_read(u8 *state);

/* scene_create_resource_transition.c */
void *scene_create_resource_transition(void *owner_arg, void *context_arg);

/* select_next_scene_mode.c */
void select_next_scene_mode(void);

/* select_second_house_map.c */
void select_second_house_map(void);

/* set_next_scene_phase.c */
void set_next_scene_phase(void);

/* shared_slot_state.c */
void render_cd_wait_animation_on_new_field(void);
void draw_cd_wait_sprite_trail(s32 blend_step);

/* slot_transition.c */
void load_scene_dispatch_resources(void);
void render_scene_until_runtime_slot_idle(void);
void await_scene_confirmation_and_reserve_slot(void);
void finish_scene_when_runtime_slot_idle(void);

/* slot_transition_secondary.c */
void load_object_scene_dispatch_resources(void);
void render_object_scene_until_slot_idle(void);
void await_object_scene_confirmation(void);
void finish_object_scene_when_slot_idle(void);

/* start_scene_load_task.c */
void start_scene_load_task(struct S_80051164 *owner);

/* update_controller_buttons_and_triggers.c */
void update_controller_buttons_and_triggers(void);

/* update_deferred_resource_transition_task.c */
void update_deferred_resource_transition_task(void *data);

/* upload_dispatch_entry_images.c */
void upload_dispatch_entry_images(u16 index);

/* upload_image_tiles.c */
void *func_80047AB0(void *object, u16 texture_page, s32 clut_id, s32 alternate_page, s32 image_addr);
void *upload_image_tiles(void *object, u16 texture_page, s32 clut_id, s32 alternate_page, s32 image_addr);

/* zero_words.c */
void *allocate_flagged_object_node(s32 flags);

/* Data declarations. */
extern u16 scene_sprite_cached_mode;
extern u16 scene_sprite_fade_ticks;
extern u8 scene_sprite_last_field;
extern void *scene_sprite_list_base;
extern s16 scene_sprite_list_initialized;
extern s16 scene_sprite_wave_tick;
extern s16 secondary_transition_slot_index;
extern s16 transition_runtime_slot_index;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void transform_vector_with_saved_matrix(GteMatrix *matrix, GteShortVector *input_vec, GteTranslationVector *output_vec);

#endif
