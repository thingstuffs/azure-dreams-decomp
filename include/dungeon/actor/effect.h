#ifndef DUNGEON_ACTOR_EFFECT_H
#define DUNGEON_ACTOR_EFFECT_H

/* Function contracts owned by src/dungeon/actor/effect/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
void *create_owner_linked_pulsing_effect(void *spawn_pos, EntityRec *source_state, void *owner);


#endif
