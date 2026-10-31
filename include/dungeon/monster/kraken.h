#ifndef DUNGEON_MONSTER_KRAKEN_H
#define DUNGEON_MONSTER_KRAKEN_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"




void update_directional_movement_and_settle(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);



void update_actor_animation_timers_and_transitions(ActorRecord *entity, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_movement_and_emit_particles(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, void *entity);

/* Callback entry points. */
void update_actor_callbacks_movement_and_terrain(ActorRecord *body, ObjectPosition *motion, void *sprite_arg);

#endif
