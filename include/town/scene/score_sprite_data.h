#ifndef TOWN_SCENE_SCORE_SPRITE_DATA_H
#define TOWN_SCENE_SCORE_SPRITE_DATA_H

#include "common.h"

/* Both score-sprite consumers read the first 32-bit value at 0x80077C68. */
extern s32 score_sprite_initial_value[];
/* Address of the imported score-sprite draw callback at 0x8003C558. */
extern u8 score_sprite_draw_callback_address[];

#endif
