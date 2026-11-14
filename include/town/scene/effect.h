#ifndef TOWN_SCENE_EFFECT_H
#define TOWN_SCENE_EFFECT_H

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"


/* advance_effect_and_reduce_scale.c */
void advance_effect_and_reduce_scale(void *effect, ObjectPosition *motion, SpriteFrameState *scale);

typedef struct EffectState {
    u8 pad_00[0x66];
    union { s16 s; u16 u; } angle;
    u8 pad_68[0x2F];
    s8 style;
    s32 context;
    struct EffectState *parent;
} EffectState;

typedef union EffectRender {
    SpriteFrameState state;
    struct {
        u8 pad_00[8];
        union { void *pointer; s32 id; } source;
    } source;
} EffectRender;

typedef struct EffectNode {
    u8 pad_00[8];
    ObjectPosition *position;
    EffectRender *render;
    void *callback;
    u8 pad_14[12];
} EffectNode;

typedef union EffectPointer {
    EffectState *state;
    EffectNode *node;
    ObjectPosition *position;
} EffectPointer;

void create_map_particle_effect(EffectState *parent, ObjectPosition *position, SpriteFrameState *unused_sprite);

/* Callback entry points. */
void fade_effect_color_until_done(void *ptr);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct SpawnSeed;
void func_8052F960(struct SpawnSeed *seed);
void func_8052FB08(struct SpawnSeed *seed);

#endif
