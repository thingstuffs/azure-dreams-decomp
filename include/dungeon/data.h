#ifndef DUNGEON_DATA_H
#define DUNGEON_DATA_H
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

extern s16 actor_event_values[ ];
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
extern s32 particle_object_flags;
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

extern s16 linked_monster_effect_updated[ 6 ];
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
extern u8 uboat_action_frames[ ];
extern u8 uboat_aura_later_frames[ ];
extern u8 uboat_aura_start_frames[ ];
extern u8 uboat_ready_frames[ ];
extern u8 uboat_timed_motion_frames[ ];
extern u8 uboat_timed_motion_frames_alt[ ];

extern SpriteSourceEntry random_motion_sprite_data_a[ ];
extern SpriteSourceEntry random_motion_sprite_data_b[ ];
extern SpriteSourceEntry random_motion_sprite_data_c[ ];

extern u16 camera_depth_index[ 5 ];
extern M2C_UNK familiar_menu_action_data;
extern u8 familiar_removed_during_change;
extern u8 player_alternate_motion_frames[ ];
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
extern u8 player_tile_motion_frames[ ];
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
extern u8 beldo_large_frame_set_18[ ];
extern u8 beldo_large_frame_set_6[ ];
extern s16 beldo_script_timer;
extern u8 encounter_transition_pool_script[ ];

#endif
