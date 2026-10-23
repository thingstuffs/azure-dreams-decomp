#ifndef DUNGEON_MONSTER_DEATH_H
#define DUNGEON_MONSTER_DEATH_H

/* Function contracts owned by src/dungeon/monster/death/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
void update_entity_movement_animation_and_ground(void *entity, ObjectPosition *motion, void *sprite);








void advance_effect_toward_target(void *effect, ObjectPosition *position);
void finish_staged_jump_at_tile_center(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void advance_actor_states_and_entity_flags(void *actor, void *context, SpriteFrameState *animation, ActorRecord *entity);

#endif
