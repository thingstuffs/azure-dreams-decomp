#ifndef TOWN_SCENE_SCORE_SPRITE_DATA_H
#define TOWN_SCENE_SCORE_SPRITE_DATA_H

#include "common.h"

/* Source word of the frame entry selected by the bounce and slot-machine sprites. */
extern void *score_sprite_initial_value[];
/* The three kind-indexed sources in the Town score image table. */
extern void *score_object_images[3];
/* Address of the imported score-sprite draw callback at 0x8003C558. */
extern u8 score_sprite_draw_callback_address[];

#endif
