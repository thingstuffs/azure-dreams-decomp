#ifndef DUNGEON_MONSTER_UNICORN_H
#define DUNGEON_MONSTER_UNICORN_H

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"



void update_actor_move_animation_and_recovery(void *action, ObjectPosition *motion, SpriteFrameState *sprite, void *actor);

void *spawn_unicorn(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

#endif
