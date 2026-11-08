#ifndef DUNGEON_MONSTER_DRAGON_TRANSITION_EFFECT_H
#define DUNGEON_MONSTER_DRAGON_TRANSITION_EFFECT_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

s32 check_actor_transition_and_start_effect(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor);
void start_directional_actor_effect(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);

#endif
