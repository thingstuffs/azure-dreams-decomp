#ifndef TOWN_SCENE_ANIMATION_H
#define TOWN_SCENE_ANIMATION_H

#include "common.h"

/* Body of the rising effect object: root link, mode, and per-frame state. */
typedef struct RisingEffectObject {
    /* 0x00 */ void *root;
    /* 0x04 */ s32 field_04;
    /* 0x08 */ s32 field_08;
    /* 0x0C */ union { s16 s; u16 u; } mode;
    /* 0x0E */ s16 field_0E;
    /* 0x10 */ u16 field_10;
} RisingEffectObject;

/* draw_rotating_collection_frame.c */
void draw_rotating_collection_frame(u8 *object);

/* Callback entry points. */
void animate_collection_center_sprite(u8 **ctrl, u8 *setup, u8 *view);
void animate_falling_timed_object(void *obj, void *motion, void *incoming_out);
void animate_rising_effect_object(RisingEffectObject *obj, void *state_in, void *input);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Actor;
struct Motion;
struct State;
void animate_bouncing_score_object(struct State *st, struct Motion *mot, struct Actor *actor);

#endif
