#ifndef TOWN_SCENE_ANIMATION_H
#define TOWN_SCENE_ANIMATION_H

#include "common.h"


/* draw_rotating_collection_frame.c */
void draw_rotating_collection_frame(u8 *object);

/* Callback entry points. */
void animate_collection_center_sprite(u8 **ctrl, u8 *setup, u8 *view);
void animate_falling_timed_object(void *obj, void *motion, void *incoming_out);
void animate_rising_effect_object(void *obj, void *state_in, void *input);

#endif
