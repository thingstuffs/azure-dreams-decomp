/* Named dungeon globals with builtin types; independent of record-layout imports. */
#ifndef DUNGEON_GLOBALS_H
#define DUNGEON_GLOBALS_H

#include "common.h"

extern s16 actor_event_values[ ];
extern u8 linked_graphic_sprite_entries;
extern s32 particle_object_flags;
extern u8 player_alternate_motion_frames[ ];
extern u8 player_put_down_frames[ ];
extern u8 player_tile_motion_frames[ ];

extern s16 actor_hop_target_height;
extern s16 lift_jitter_offsets[2];
extern s32 visual_object_sprite_data;

/* Number of frames left in the dungeon camera target transition. */
extern u8 camera_transition_timer;

/* The actor replacement fade interpolates the scene tint toward one of four
 * four-byte colours. Only the first three bytes are read; the fourth is zero. */
typedef struct ActorEffectColor {
    u8 r, g, b;
    u8 pad;
} ActorEffectColor;
extern ActorEffectColor *actor_effect_color_targets[4];

#endif
