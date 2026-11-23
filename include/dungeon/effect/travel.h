#ifndef DUNGEON_EFFECT_TRAVEL_H
#define DUNGEON_EFFECT_TRAVEL_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "dungeon/effect/spell_effect.h"



/* Target-tracking work passed at node +0x20 to update_accelerating_condition_projectile. The signed
 * packed tile pairs are compared together when the effect crosses a tile. */
typedef union TrackingTilePair {
    s16 packed;
    struct { union { s8 s; u8 u; } x, y; } tile;
} TrackingTilePair;

typedef struct TrackingEffect {
    ActorRecord *owner;
    struct { u16 flags; } *animation;
    u8 pad_08;
    u8 variant;
    u16 state;
    void *child;
    u16 target_x;
    u16 target_y;
    s16 target_z;
    u8 flags;
    u8 pad_17;
    u16 tiles_left;
    s16 direction;
    u16 unk_1C;
    u8 pad_1E[2];
    TrackingTilePair current_tile;
    TrackingTilePair previous_tile;
    u8 pad_24[4];
    s16 sound_played;
} TrackingEffect;

/* Work of the effect follow_brighten runs: the spell effect prefix, the target position, the packed tile pairs
 * compared when the effect crosses a tile, the child effect it spawns on arrival and a 16.16 height. */
typedef struct FollowBrightenEffect {
    SpellEffectHeader spell;
    u16 target_x; /* target world X, integer half */
    u16 target_y; /* target world Y, integer half */
    s16 target_z; /* target height the effect closes on, integer half */
    u8 flags; /* 4: the sprite was registered for drawing */
    u8 pad_13;
    u16 tiles_left; /* tiles left to cross before the effect fades */
    s16 direction; /* actor facing as a direction index 0..7 */
    s16 frame_count; /* updates since creation; its sine lifts the effect */
    u8 pad_1A[2];
    u8 pad_1C[2];
    TrackingTilePair current_tile;
    TrackingTilePair previous_tile;
    u8 pad_22[0xA];
    ObjectNodeHeader *child; /* the effect spawned on arrival; its node flags show completion */
    Fixed1616 height; /* travel height, 16.16 */
} FollowBrightenEffect;

/* Target and phase counter carried by the red tint effect emitted during travel. */
typedef struct BrighteningFollowerEffectBody {
    ActorRecord *target;
    u8 pad_04[0x6];
    u16 state;
    u8 pad_0C[0x10];
    u16 particle_count;
} BrighteningFollowerEffectBody;

/* State for each ring particle emitted while update_accelerating_condition_projectile is active. */
typedef struct RisingFadingEmitterBody {
    u8 pad_00[0xA];
    u16 state;
    u8 pad_0C[0x8];
    s16 height_limit;
    u8 pad_16[0x6];
    u16 frame_count;
    u16 initial_delay;
    u8 pad_20[0x4];
    s16 effect_value;
} RisingFadingEmitterBody;

void update_accelerating_condition_projectile(TrackingEffect *self, ObjectPosition *motion, SpriteFrameState *part);

void follow_brighten(FollowBrightenEffect *self, ObjectPosition *motion, SpriteFrameState *part);

void advance_rising_fading_emitter(RisingFadingEmitterBody *effect, ObjectPosition *motion, SpriteFrameState *primitive);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "shared/dungeon_moving_views.h"
void *create_tinted_travel_sprite(ObjectPosition *source_pos, s16 effect_param, s16 size);

#endif
