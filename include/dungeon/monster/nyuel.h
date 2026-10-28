#ifndef DUNGEON_MONSTER_NYUEL_H
#define DUNGEON_MONSTER_NYUEL_H

/* Function contracts owned by src/dungeon/monster/nyuel/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
s32 check_movement_and_initialize_action(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);
void start_directional_animation_if_allowed(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_movement_and_tile_position(ActorRecord *object, ObjectPosition *entry_context, SpriteFrameState *tile, ActorRecord *actor);





void move_actor_with_vertical_arc(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_actor_state_and_directional_effect(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);



void advance_action_phases_and_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);
void func_80171B58(void *action, s32 context, SpriteFrameState *sprite, void *state);

void create_cylindrical_effect(ActorRecord *source, ObjectPosition *origin);

#endif
