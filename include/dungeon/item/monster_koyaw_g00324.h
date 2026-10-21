#ifndef DUNGEON_ITEM_MONSTER_KOYAW_G00324_H
#define DUNGEON_ITEM_MONSTER_KOYAW_G00324_H
/* Monster koyaw shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_8009A9F0. */

#include "common.h"
#include "shared/game_work.h"

extern u8 D_800DD83C[];
extern u8 D_800DD840[];
extern u8 D_800DD844[];
extern u8 D_800DD848[];
extern u8 D_800DD84C[];
extern u8 D_800DD850[];

/* Functions defined in this translation unit. */
void itm_mon_koyaw_set(u8 *src, s8 *dst);
void apply_monster_koyaw_data(s32 flags, s8 *dst);

#endif
