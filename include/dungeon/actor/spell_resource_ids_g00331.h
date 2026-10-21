#ifndef DUNGEON_ACTOR_SPELL_RESOURCE_IDS_G00331_H
#define DUNGEON_ACTOR_SPELL_RESOURCE_IDS_G00331_H
/* Spell resource ids shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800A3C30, PD:dungeon/engine:800DD8E7. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

typedef struct Inner {
    u8 pad[1];
    u8 flag;
} Inner;

extern u8 D_800DD8E7[9];

/* Functions defined in this translation unit. */
s32 resolve_spell_effect_resource_id(s16 index);
s32 resolve_alternate_spell_id(s32 tile_index);

#endif
