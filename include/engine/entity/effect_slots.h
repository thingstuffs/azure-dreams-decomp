#ifndef ENGINE_ENTITY_EFFECT_SLOTS_H
#define ENGINE_ENTITY_EFFECT_SLOTS_H

#include "common.h"

struct ActorRecord;

s32 get_entity_effect_value(struct ActorRecord *entry, s32 effect_id);
void clear_slots_of_type(struct ActorRecord *owner, s8 match_type);

#endif
