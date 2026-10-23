#ifndef DUNGEON_MONSTER_GARUDA_H
#define DUNGEON_MONSTER_GARUDA_H

/* Function contracts owned by src/dungeon/monster/garuda/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void update_object_movement_facing_terrain(void *obj, void *input_motion, SpriteFrameState *input_part);




void advance_entity_directional_events(void *entity, void *context, SpriteFrameState *sprite, ActorRecord *actor);

#endif
