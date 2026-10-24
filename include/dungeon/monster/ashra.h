#ifndef DUNGEON_MONSTER_ASHRA_H
#define DUNGEON_MONSTER_ASHRA_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

void *spawn_ashra(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);
void advance_actor_motion_action(void *action_state, void *position, SpriteFrameState *sprite, ActorRecord *actor);
void complete_actor_jump_to_destination(void *jump, void *motion, void *sprite, void *actor);
void advance_actor_attack_and_resolve_damage(void *action, s32 actor_id, void *sprite, ActorRecord *actor);

#endif
