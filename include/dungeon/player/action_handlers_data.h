#ifndef DUNGEON_PLAYER_ACTION_HANDLERS_DATA_H
#define DUNGEON_PLAYER_ACTION_HANDLERS_DATA_H

#include "common.h"

/* Actor action callbacks receive the four current actor contexts. */
typedef s32 (*PlayerActionHandler)(void *, void *, void *, void *);
extern PlayerActionHandler player_action_handlers[];

#endif
