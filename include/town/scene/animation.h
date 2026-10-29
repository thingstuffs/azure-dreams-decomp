#ifndef TOWN_SCENE_ANIMATION_H
#define TOWN_SCENE_ANIMATION_H

#include "common.h"


/* draw_rotating_collection_frame.c */
void draw_rotating_collection_frame(u8 *object);

/* Callback entry points. */
void animate_collection_center_sprite(u8 **ctrl, u8 *setup, u8 *view);
void animate_falling_timed_object(void *obj, void *motion, void *incoming_out);
void animate_rising_effect_object(void *obj, void *state_in, void *input);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct Actor;
struct Motion;
struct State;
void animate_bouncing_score_object(struct State *st, struct Motion *mot, struct Actor *actor);

#endif
