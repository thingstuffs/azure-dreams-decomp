#ifndef TOWN_DATA_H
#define TOWN_DATA_H
/* Imported data declarations for this image; maintained by tools/headers. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/gpu_packets.h"
#include "shared/item_menu.h"
#include "shared/movie_list.h"
#include "shared/object_node.h"
#include "shared/sprite_source.h"
#include "shared/town_state.h"
#include "shared/vector.h"

struct DisplayPair;
struct Entry;
struct Func808816D8Owner;
struct S_800C830C_0;
struct S_8065C17C_0;
struct TownRecord;


/* Data declarations. */
extern ObjectNodeHeader *betting_display_object;
extern u8 building_palette_backup[ ];
extern u8 building_texture_backup[ ];
extern u8 building_texture_frame_one[ ];
extern u8 building_texture_frame_three[ ];
extern u8 building_texture_frame_two[ ];
extern u8 building_texture_frame_zero[ ];
extern int card_server_initialized[ 3 ];
extern struct Entry *catalog_cache_head;
extern u8 catalog_detail_fallback[ 16 ];
extern void *catalog_detail_pages[ 4 ];
extern u8 catalog_glyph_blend_table[ ];
extern s16 catalog_glyph_pixels[ ];
extern u8 catalog_habitat_label[ 16 ];
extern s16 catalog_lookup_count;
extern u8 catalog_number_prefix[ 16 ];
extern u16 catalog_override_glyph[ ];
extern void *catalog_selected_digits[ 10 ];
extern u8 catalog_selection_state[ ];
extern u32 catalog_texture_buffer[ ];
extern u32 catalog_texture_pixels[ ];
extern u8 catalog_texture_request[ ];
extern s32 *catalog_texture_resources[ ];
extern u8 catalog_unavailable_marker[ 16 ];
extern s32 devkit_cursor_state[ ];
extern u8 devkit_flag_ids[ ];
extern s32 devkit_flag_test_result;
extern SpriteSourceEntry emote_sprite_entries[ ];
extern u8 gym_object_state_address[ ];
extern s32 gym_sprite_source;
extern u16 high_display_best_score[ ];
extern u8 item_display_chain_indices[ ];
extern u8 item_menu_slot_handler_address[ ];
extern s32 keima_panel_object[ ];
extern s16 keima_payout_factors[ ];
extern u8 map_particle_first_sprite_entries[ ];
extern void *map_particle_part_parameters[ ];
extern u8 map_particle_second_sprite_entries[ ];
extern s32 menu_alternate_value_table;
extern s32 menu_paired_values[ ];
extern s32 menu_value_backup;
extern u8 minigame_actor_bounds[ ];
extern u8 minigame_display_callback_b[ ];
extern u32 minigame_image_backup[ ];
extern u8 minigame_motion_frames[ ];
extern u32 minigame_palette_backup[ ];
extern s32 minigame_pickup_sprite_sources[ ];
extern u8 minigame_sprite_entries[ ];
extern u8 monster_display_chain_indices[ ];
extern s8 mother_event_reset_byte;
extern s32 person_menu_object_entries[ ];
extern s32 person_reaction_object_entries[ ];
extern s8 person_slot_reset_byte;
extern s32 pickup_reward_total[ ];
extern s32 player_event_handler_entries;
extern s32 player_motion_bounds[ 4 ];
extern u8 pool_palette_rect[ ];
extern u8 pool_palette_rect_2[ ];
extern s32 radial_sprite_entries;
extern s32 record_action_update_address;
extern s32 ring_segment_count;
extern s32 ring_segment_counts[ ];
extern s32 scene_handler_ready;
extern s32 scene_stored_handler_value;
extern s32 selected_menu_value;
extern s32 *selected_menu_value_target;
extern u8 shop_display_presets[ ];
extern s32 *shop_indexed_flag_words[ ];
extern u8 shop_node_order[ ];
extern s16 shop_resident_flag_ids[ ];
extern s32 slot_bet_display_object[ ];
extern s16 slot_payout_digits[ 8 ];
extern u8 snowball_actor_sprites[ ];
extern volatile u16 snowball_best_score;
extern u16 tako_best_score;
extern u8 tako_particle_sprite_data[ ];
extern u8 tako_target_timing_table[ ];
extern s16 terrain_height_limits[ ];
extern s32 timed_scene_handler_entries;
extern s32 town_actor_scratch;
extern u8 town_building_scene_index;
extern u16 town_facing_angles[ ];
extern s32 town_item_layout_coordinates[ ] [ 3 ];
extern void *town_map_entry_list[ ];
extern u8 town_map_event_kind;
extern u8 town_map_optional_entry[ ];
extern s32 town_map_resource_ids[ ];
extern u8 town_minigame_directional_frames[ ];
extern s32 town_object_defaults[ ];
extern s32 town_object_resource_table[ ];
extern u8 town_overlay_rotation_offset[ ];
extern s32 town_player_target_adjustment;
extern s32 *town_position_entry_samples;
extern s32 *town_probe_adjustment_samples;
extern s32 town_record_capacities[ ];
extern s32 town_scene_init_callback;
extern s32 town_secondary_callback_state[ ];
extern s32 town_threshold_interaction_address;
extern s32 town_x_acceleration[ 4 ];
extern s32 town_x_speed_limits[ 4 ];
extern s32 town_y_acceleration[ 4 ];
extern s32 town_y_speed_limits[ 4 ];
extern u32 view_gray_command[ ];

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct TownRecord;
extern s32 betting_round_handle[ 3 ];
extern u8 betting_sprite_animation[ ];
extern u8 keima_entries[ ];
extern u8 keima_flag_conditions[ ];
extern s32 scene_charge;
extern s32 scene_choice_values[ ];
extern s32 scene_command_result;
extern void *scene_current_cell_pointer;
extern s32 scene_current_entry_value;
extern s16 scene_dependency_ids[ 3 ];
extern s16 scene_event_test_id;
extern s16 scene_gate_script_flag;
extern u8 scene_mode_response_data[ ];
extern s32 scene_object_flags;
extern u8 scene_pair_dispatch_context[ ];
extern s32 scene_price;
extern struct TownRecord *scene_record_list;
extern s32 scene_registered_data_handle;
extern s32 scene_registered_entry_handle;
extern s32 scene_response_enabled;
extern s32 scene_saved_player_value;
extern s32 scene_second_component_values[ ];
extern u8 scene_shared_text_buffer[ ];
extern s32 scene_stored_first_value;
extern s16 scene_threshold_counter;
extern u8 score_bounce_update_address[ ];
extern u8 score_sprite_handler_address[ ];
extern s32 script_rescan_request;
extern u8 shop_panel_sprite_entries[ ];
extern void *slot_machine_bet_effect[ ];
extern u8 slot_machine_symbol_strips[ ] [ 12 ];
extern u8 town_counted_record_ids[ ];
extern u8 town_enabled_entry_order[ ];
extern u8 town_entry_check_zero[ ];
extern s16 town_event_counter;
extern u8 town_event_value_list[ ];
extern u8 town_hud_image_data[ ];
extern u8 town_hud_object_template[ ];
extern s32 town_indexed_event_values[ ];
extern IntVector3 town_player_fixed_position;
extern s32 town_repeat_value_selected;
extern s16 town_response_key_indices[ ];
extern s32 town_secondary_price;
extern s32 town_selected_valid_entry[ ];
extern s32 town_service_fixed_position;
extern s32 town_stored_amount;
extern u8 town_wrapped_entry_order[ ];

#endif
