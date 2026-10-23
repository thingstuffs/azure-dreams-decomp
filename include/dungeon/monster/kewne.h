#ifndef DUNGEON_MONSTER_KEWNE_H
#define DUNGEON_MONSTER_KEWNE_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void advance_actor_action_and_refresh_animation(void *actor, void *context, SpriteFrameState *render_record, ActorRecord *actor_state);
void update_movement_height_and_animation(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);
void update_staged_movement_and_idle(void *action, ObjectPosition *movement, SpriteFrameState *sprite, void *actor);

#endif
