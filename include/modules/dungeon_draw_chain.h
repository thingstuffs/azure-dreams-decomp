#ifndef DUNGEON_DRAW_CHAIN_H
#define DUNGEON_DRAW_CHAIN_H
#include "common.h"
struct ObjectPosition;
struct SpriteFrameState;
/* Registered draw callback: payload, position, rendering state; returns zero. */
s32 draw_linked_object_chain(void *payload, struct ObjectPosition *position, struct SpriteFrameState *sprite);
#endif
