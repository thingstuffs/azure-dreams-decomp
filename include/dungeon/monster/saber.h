#ifndef DUNGEON_MONSTER_SABER_H
#define DUNGEON_MONSTER_SABER_H

#include "common.h"
#include "shared/entity.h"

/* Monster-owned imports; preserve their registered declaration contracts. */
extern s32 saber_behavior_entry;
extern u8 saber_direction_frames[];
extern u8 saber_direction_frames_2[];

void finish_saber_tile_hop(void *action, ObjectPosition *motion, void *sprite, ActorRecord *entity);

#endif
