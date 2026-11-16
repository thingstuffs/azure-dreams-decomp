#ifndef DUNGEON_MONSTER_GRIFFON_ACTION_CALLBACK_ADDRESSES_H
#define DUNGEON_MONSTER_GRIFFON_ACTION_CALLBACK_ADDRESSES_H

#include "shared/entity.h"

/* Placed copies of update_griffon_actor_behavior in the two Griffon banks. */
void griffon_slot_a_action_callback(ActorRecord *actor, ObjectPosition *position,
                                    struct SpriteFrameState *sprite, ActorRecord *actor_data);
void griffon_slot_d_action_callback(ActorRecord *actor, ObjectPosition *position,
                                    struct SpriteFrameState *sprite, ActorRecord *actor_data);

#endif
