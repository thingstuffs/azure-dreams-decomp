#ifndef DUNGEON_MONSTER_GHOSH_H
#define DUNGEON_MONSTER_GHOSH_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern u8 ghosh_direction_frames[];
extern u8 ghosh_ready_action_frames[];

void create_boss_child_effect(void *parent_data, MovingPosition *source_pos, void *sprite_template);
void create_boss_directional_effect(void *source, s16 angle, s32 initial_value, s32 unused, s16 spread_mode);
void release_secondary_overlay_object(void);


void update_boss_actor_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);



void update_actor_animation_movement_and_terrain(void *entity, ObjectPosition *motion, void *sprite);
void update_boss_actor_movement(void *entity, ObjectPosition *motion, SpriteFrameState *sprite);

typedef union GhoshFadeColor {
    s32 word;
    struct { s8 r, g, b, pad; } rgb;
} GhoshFadeColor;

typedef struct GhoshTrailFade {
    u8 r, g, b, pad03;
    GhoshFadeColor scaled;
    s32 color;
    u8 pad0C[0x26];
    union { s16 s; u16 u; } steps;
    s16 divisor;
} GhoshTrailFade;

void advance_ghosh_trail_fade(GhoshTrailFade *fade, ObjectPosition *position);

/* Callback entry points. */
void advance_three_state_bytes(u16 *words);
void animate_timed_fade_effect(void *effect);
void apply_boss_direction_table_state(void *record_data);
void update_object_motion_and_landing(void *motion, void *position, void *object);

#endif
