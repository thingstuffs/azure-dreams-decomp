#ifndef DUNGEON_EFFECT_TRAVEL_H
#define DUNGEON_EFFECT_TRAVEL_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



/* Target-tracking work passed at node +0x20 to follow_brighten. The signed
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
    union { s16 s; u16 u; } state;
    void *child;
    u16 target_x;
    u16 target_y;
    union { s16 s; u16 u; } target_z;
    u8 flags;
    u8 pad_17;
    u16 tiles_left;
    union { s16 s; u16 u; } direction;
    u16 unk_1C;
    u8 pad_1E[2];
    TrackingTilePair current_tile;
    TrackingTilePair previous_tile;
    u8 pad_24[4];
    s16 sound_played;
} TrackingEffect;

void follow_brighten(TrackingEffect *self, ObjectPosition *motion, SpriteFrameState *part);

void advance_rising_fading_emitter(void *effect, ObjectPosition *motion, SpriteFrameState *primitive);

#endif
