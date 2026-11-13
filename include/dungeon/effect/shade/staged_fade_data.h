#ifndef DUNGEON_EFFECT_SHADE_STAGED_FADE_DATA_H
#define DUNGEON_EFFECT_SHADE_STAGED_FADE_DATA_H

#include "common.h"

/* One two-byte counter: the shade producers increment it, the transition
 * consumer tests it for zero, clears it and advances it from a widened copy. */
extern s16 staged_fade_count;

#endif
