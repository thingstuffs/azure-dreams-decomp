#ifndef DUNGEON_MONSTER_PICKET_H
#define DUNGEON_MONSTER_PICKET_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_a_jump_toward_target_tile_restores_actor_finishes(void *jump_state, ObjectPosition *motion, SpriteFrameState *map_entity, ActorRecord *actor);
void update_movement_animation_settles_actor_target_tile(void *action, void *motion, SpriteFrameState *sprite, void *actor);



void update_a_timed_movement_animation_marks_completion(void *actor, ObjectPosition *motion, SpriteFrameState *visual);
void update_movement_destination_selection_recovery_animation(void *state, ObjectPosition *motion, SpriteFrameState *actor, void *object);

#endif
