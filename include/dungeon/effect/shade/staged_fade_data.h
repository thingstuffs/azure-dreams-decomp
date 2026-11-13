#ifndef DUNGEON_EFFECT_SHADE_STAGED_FADE_DATA_H
#define DUNGEON_EFFECT_SHADE_STAGED_FADE_DATA_H

#include "common.h"
#include "shared/dungeon_moving_views.h"

/* One two-byte counter: shade producers increment it as unsigned; the
 * transition consumer also tests the same bits as a signed value. */
extern BankEffectCounter staged_fade_count;

#endif
