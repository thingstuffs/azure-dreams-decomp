#ifndef DUNGEON_OVL_1876800_H
#define DUNGEON_OVL_1876800_H
#include "common.h"
#include "modules/dungeon_native_abi.h"

/* The object an effect belongs to: bit 0x8000 of its +0x52 flag word marks it. */
typedef struct EffectOwner {
    u8 pad_00[0x52];
    u16 flags;
} EffectOwner;

/* The effect's own record; the 0x20-byte ObjectNodeHeader sits right before it. */
typedef struct EffectRecord {
    EffectOwner *owner;
    u8 pad_04[0x44];
    u16 timer;       /* 0x48: frames to wait in state 0 */
    s16 fade_step;   /* 0x4A: brightness removed per frame in state 1 */
    s16 state;       /* 0x4C: 0 = wait, 1 = fade the sprite */
} EffectRecord;


void advance_motion_and_fade_sprite(EffectRecord *, ObjectPosition *, SpriteFrameState *);
s32 project_linked_shape_quads(void *);
#endif
