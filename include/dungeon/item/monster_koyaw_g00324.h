#ifndef DUNGEON_ITEM_MONSTER_KOYAW_G00324_H
#define DUNGEON_ITEM_MONSTER_KOYAW_G00324_H
/* Monster koyaw shared declarations. */

#include "common.h"
#include "shared/game_work.h"

extern u8 neutral_status_tint_color[];
extern u8 confused_status_tint_color[];
extern u8 mp_empty_status_tint_color[];
extern u8 poisoned_status_tint_color[];
extern u8 blind_status_tint_color[];
extern u8 paralyzed_status_tint_color[];

/* Functions defined in this translation unit. */
void compute_pulsing_tint_offsets(u8 *src, s8 *dst);

#endif
