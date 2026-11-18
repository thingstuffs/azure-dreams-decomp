#ifndef DUNGEON_ACTOR_SPELL_RESOURCE_IDS_DATA_H
#define DUNGEON_ACTOR_SPELL_RESOURCE_IDS_DATA_H

#include "common.h"

/* Resident dungeon table at 0x800DD8E7: 49 bytes before the next spell table. */
extern u8 spell_resource_ids[49];

/* create_actor_spell_effect copies the variant byte from the spell record here. */
extern u8 current_spell_effect_variant;

#endif
