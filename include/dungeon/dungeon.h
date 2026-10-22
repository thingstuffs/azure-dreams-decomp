#ifndef DUNGEON_DUNGEON_H
#define DUNGEON_DUNGEON_H
#include "common.h"
#include "shared/sprite_frame_state.h"
struct PairAction;
struct ActorMotion;
struct ActorSprite;
void advance_paired_actor_transfer(struct PairAction *actor, struct ActorMotion *motion, SpriteFrameState *sprite, void *entity);
#endif
