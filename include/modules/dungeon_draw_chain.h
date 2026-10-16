#ifndef DUNGEON_DRAW_CHAIN_H
#define DUNGEON_DRAW_CHAIN_H
#include "common.h"
/* Registered draw callback: payload, position, rendering state; returns zero. */
s32 dungeonDrawLinkedObjectChain(void *payload, void *position, void *render);
#endif
