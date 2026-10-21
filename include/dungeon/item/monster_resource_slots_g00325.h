#ifndef DUNGEON_ITEM_MONSTER_RESOURCE_SLOTS_G00325_H
#define DUNGEON_ITEM_MONSTER_RESOURCE_SLOTS_G00325_H
/* Monster resource slots shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_8009BE50, PD:dungeon/engine:800E3DA0, PD:dungeon/engine:800E3DB0, PD:dungeon/engine:800E3DD0, PD:dungeon/engine:800E3DE0. */

#include "common.h"

#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))

extern u8 D_800E3DB0[];
extern void retain_sprite_resource_in_cache(s16);
extern u8 D_800E3DA0[];
extern u8 D_800E3DE0[];
extern u8 D_800E3DD0[];
extern void mark_sprite_resource_for_purge(s32);

/* Functions defined in this translation unit. */
s32 has_matching_six_slot_entry(s32 entry_id_word);
u8 *find_or_retain_sprite_resource_slot(s32 requested_id, s32 requested_type);
u8 *find_monster_entry_by_type_and_id(s16 entry_id, s32 entry_type);
void decrement_monster_entry_count(s16 requested_id, s16 requested_type);

#endif
