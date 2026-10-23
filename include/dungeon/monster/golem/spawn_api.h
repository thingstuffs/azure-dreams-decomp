#ifndef INCLUDE_DUNGEON_MONSTER_GOLEM_SPAWN_API_H
#define INCLUDE_DUNGEON_MONSTER_GOLEM_SPAWN_API_H

/* Contracts owned by src/dungeon/monster/golem/spawn_golem.c. */
#include "common.h"

void *create_golem_actor(s16 spawn_flags, s32 tile_x, s32 tile_y, s32 spawn_height);

#endif
