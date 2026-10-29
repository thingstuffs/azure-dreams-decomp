#ifndef DUNGEON_ITEM_MONSTER_RESOURCE_SLOTS_G00325_H
#define DUNGEON_ITEM_MONSTER_RESOURCE_SLOTS_G00325_H
/* Monster resource slots shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_8009BE50, PD:dungeon/engine:800E3DA0, PD:dungeon/engine:800E3DB0, PD:dungeon/engine:800E3DD0, PD:dungeon/engine:800E3DE0. */

#include "common.h"

#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))

extern u8 monster_resource_cache_slots[];
extern s32 retain_sprite_resource_in_cache(s16 slot_id);
extern s8 monster_resource_cache_ids[];
extern u8 monster_fixed_resource_slot[];
extern u8 D_800E3DD0[];

/* The bank's first word is a spawn entry; the slot caches that same address at +4. */
typedef void *(*MonsterFactory)(s32 flags, s16 tile_x, s16 tile_y, s16 height);
typedef struct MonsterResourceSlot {
    u8 type;
    u8 resource_id;
    u8 count;
    u8 cache_index;
    MonsterFactory factory;
} MonsterResourceSlot;

MonsterFactory load_monster_resource_data(s32 resource_id, void *resource_entry, s32 wait_for_read);

/* Functions defined in this translation unit. */
s32 has_matching_six_slot_entry(s32 entry_id_word);
u8 *find_or_retain_sprite_resource_slot(s32 requested_id, s32 requested_type);
void decrement_monster_entry_count(s16 requested_id, s16 requested_type);

#endif
