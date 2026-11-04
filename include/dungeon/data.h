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

#endif
