#ifndef DUNGEON_MONSTER_GARUDA_H
#define DUNGEON_MONSTER_GARUDA_H

/* Function contracts owned by src/dungeon/monster/garuda/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void update_object_movement_facing_terrain(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite);




void advance_entity_directional_events(void *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);

void update_creature_animation_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *creature);

#endif
