#ifndef DUNGEON_DATA_H
#define DUNGEON_DATA_H
#include "dungeon/globals.h"
#include "dungeon/monster/stealth_frames.h"
#include "dungeon/monster/viper_frames.h"
#include "dungeon/monster/u_boat_frames.h"
#include "dungeon/monster/weadog_frames.h"
#include "dungeon/monster/baloon_frames.h"
/* Imported data declarations for this image; maintained by tools/headers. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_particle_template.h"
#include "shared/dungeon_trail_views.h"
#include "shared/entity.h"
#include "shared/entity_action_selectors.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_source.h"

struct CallbackEntry;
struct S_800B50B0_Entity;


/* Data declarations. */
extern u8 manoeva_frame_set[ ];

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
extern u8 beldo_large_frame_set_14[ 16 ];
extern u8 beldo_large_frame_set_8[ 16 ];

extern u8 familiar_call_text[ ];
extern u8 genus_change_text[ ];
extern u8 *item_type_text_prefixes[ ];
extern u8 *item_type_text_suffixes[ ];

extern u8 confusion_cure_text[ ];
extern u16 magic_ball_delay[ ];
extern u8 monster_module_read_descriptor[ ];
extern u16 monster_special_entry_index;
extern u8 poison_cure_text[ 25 ];

extern s16 bounded_runtime_counter;
extern u8 fullwidth_period[ ];
extern s32 item_panel_display_ids;
extern s32 saved_random_seed[ ];

extern u8 *dungeon_menu_text_entries[ ];
extern u8 dungeon_palette_row_sources[ ];
extern s32 menu_alternate_value_table;
extern s32 menu_paired_values[ ];
extern s32 menu_value_backup;
extern u8 numeric_character_flags[ ];
extern u8 packed_tile_heights[ ];
extern s32 selected_menu_value;

extern u16 dungeon_status_flags_alias;

extern u8 battle_message_buffers[ ];

extern u8 child_particle_draw_address[ ];
extern u8 countdown_sprite_entries[ ];
extern u8 directional_effect_entries[ ];
extern s16 linked_effect_chain_count[ 6 ];
extern s16 parent_effect_update_flag;
extern u8 particle_fade_pixels[ ];
extern u8 spark_sprite_entries[ ];
extern s32 tile_actor_sprite_entries;

extern u8 actor_attack_frames[ ];
extern s16 camera_depth_target[ 5 ];
extern u8 camera_height_tracking[ ];
extern u16 effect_saved_position[ ];
extern u8 familiar_defeat_text[ ];
extern u8 familiar_save_alt_frames[ ];
extern u8 familiar_save_frames[ ];
extern u8 familiar_save_restore_frames[ ];
extern u8 particle_target_height[ ];
extern u8 pending_player_damage_kind;
extern u8 player_attack_frames[ ];
extern u8 player_attack_start_frames[ ];

extern s16 linked_effect_chain_updated[ 6 ];
extern u8 screen_effect_sprite_entries[ 12 ];
extern u8 screen_transition_pixels[ ];

extern u8 paired_random_effect_callback[ 12 ];
extern u8 radial_effect_colors[ ];
extern M2C_UNK radial_effect_frames;
extern u8 ring_effect_work[ ];
extern u8 staged_glow_data[ ];

extern u8 mesh_edge_payload_template[ 12 ];
extern s16 point_cloud_update_flag[ 5 ];

extern u8 shaded_quad_frame_set[ 9 ];

extern SpriteSourceEntry random_motion_sprite_data_a[ ];
extern SpriteSourceEntry random_motion_sprite_data_b[ ];
extern SpriteSourceEntry random_motion_sprite_data_c[ ];

extern u16 camera_depth_index[ 5 ];
extern M2C_UNK familiar_menu_action_data;
extern u8 familiar_removed_during_change;
extern u8 player_damage_frames[ ];
extern u8 player_height_step_frames[ ];
extern u8 player_hop_frames[ ];
extern u32 player_idle_turn_count;
extern u8 player_jump_frame_set[ 8 ];
extern u8 player_landing_frame_set[ ];
extern u8 player_push_frames[ ];
extern u8 player_push_loop_frames[ ];
extern u8 player_push_start_frames[ ];
extern u8 player_sleep_frames;
extern u8 player_throw_followup_frames[ 8 ];
extern s32 player_turn_fraction;
extern u8 return_magic_frames[ ];
extern s32 selected_item_action_alias;

extern u16 actor_direction_dispatch_key;
extern s16 beldo_camera_position[ 4 ];
extern s16 beldo_camera_rotation[ 4 ];
extern u8 beldo_large_frame_set[ 8 ];
extern u8 beldo_large_frame_set_10[ 8 ];
extern u8 beldo_large_frame_set_11[ ];
extern u8 beldo_large_frame_set_15[ 8 ];
extern u8 beldo_large_frame_set_16[ 8 ];
extern u8 beldo_large_frame_set_17[ ];
#include "dungeon/monster/beldo_large_frames.h"
extern u8 beldo_large_frame_set_6[ ];
extern s16 beldo_script_timer;
extern u8 encounter_transition_pool_script[ ];

extern u8 ghosh_frame_set_1[ ];
extern u8 ghosh_frame_set_11[ ];
extern u8 ghosh_frame_set_2[ ];
extern u8 ghosh_frame_set_5[ ];
extern u8 ghosh_frame_set_6[ ];
extern u8 ghosh_motion_path[ ];
extern u8 kid_effect_load_done;
extern u32 kid_image_commands;
extern u8 kid_image_load_done;
#include "dungeon/monster/kraken_frames.h"
extern u8 kraken_frame_set_3[ ];
extern u8 nyuel_effect_load_done[ ];
extern u32 nyuel_image_commands;
extern u8 nyuel_image_load_done[ ];
extern u8 picket_frame_set_8[ ];
extern s32 scene_deferred_dispatch_address;
extern s32 scene_idle_callback_address;
extern u8 species_base_stats[ ];
extern char stack_split_text[ ];
extern u8 status_name_separator[ 12 ];
extern s32 town_busy_countdown_address;
extern s32 town_input_object_address;
extern s32 town_radial_motion_address;
extern s32 town_threshold_update_address;
extern u8 troll_slot_c_action_callback[ ];
extern u8 unicorn_effect_load_done[ ];
extern s32 unicorn_image_load_done[ ];

extern u8 baloon_fall_frames[ 8 ];
#include "dungeon/monster/barong_frames.h"

#include "dungeon/monster/beldo_frames.h"
extern u8 beldo_frame_set_3[ 8 ];
extern u8 child_object_update_address[ ];
extern u8 child_texture_entries[ ];
extern u8 death_frame_set_4[ 8 ];
extern u8 death_frame_set_5[ 8 ];
extern u8 death_frame_set_6[ 8 ];
extern u8 ghosh_command_f0_frames[ ];
extern u8 ghosh_command_f8_frames[ ];
extern u8 ghosh_frame_bank[ ];
extern u8 ghosh_frame_set_13[ ];
#include "dungeon/monster/ghosh_frames.h"

extern u8 ghosh_frame_set_8[ ];
extern u8 ghosh_frame_set_9[ ];
extern u8 hikewne_frame_set_14[ ];
extern u8 hikewne_frame_set_15[ ];
extern u8 metal_frame_set_2[ ];
extern u8 metal_movement_frames[ ];
extern u8 naplass_frame_set_2[ ];
extern u8 naplass_frame_set_3[ ];
extern u8 nyuel_frame_set_10;
extern u8 nyuel_frame_set_4;
extern u8 nyuel_frame_set_9;
extern u8 picket_frame_set_1[ ];
extern u8 picket_frame_set_2[ ];
extern u8 saber_frame_set[ ];
#include "dungeon/monster/saber_frames.h"

extern u8 ashra_frame_set_1[ ];
extern u8 ashra_frame_set_2[ ];


extern s32 beldo_old_transition_flags[ 3 ];
extern u8 garuda_frame_set_3[ ];
extern u8 garuda_walk_text[ 16 ];
extern u8 golem_frame_set_2;
extern u8 golem_frame_set_4[ 8 ];
#include "dungeon/monster/troll_frames.h"


extern u8 uboat_aura_sprite_data[ ];

extern u8 griffon_frame_set_9[ ];
extern u8 griffon_slot_c_action_callback;
extern u8 grineut_frame_set_10[ ];
extern u8 grineut_frame_set_12[ ];
extern u8 grineut_frame_set_9[ ];
extern u8 grineut_slot_c_action_callback;
extern u8 grineut_slot_d_action_callback;
extern u8 grineut_slot_f_action_callback;
extern u8 hikewne_frame_set_16[ ];
extern u8 hikewne_frame_set_17[ ];
extern u8 kewne_frame_set_4[ ];
extern u32 kewne_palette_colors[ ];
extern u8 kewne_turn_frames[ ];
extern u8 kraken_action_handlers[ ];
extern u8 kraken_frame_set_5;
extern u8 metal_frame_set_1[ ];
#include "dungeon/monster/nyuel_frames.h"
extern u8 picket_frame_set_4[ ];
extern s32 picket_slot_f_item_result[ ];
extern u8 pulunpa_frame_set_1[ ];

extern u8 ashra_frame_set_3[ ];
extern u8 tyrant_frame_set_1[ ];
extern u8 unicorn_frame_set_1[ ];

extern u8 actor_surface_callback_address[ ];
extern u8 linked_object_draw_address[ ];
extern u8 player_move_frames[ ];
extern s32 *selected_menu_value_target;
extern s16 terrain_height_limits[ ];

#endif
