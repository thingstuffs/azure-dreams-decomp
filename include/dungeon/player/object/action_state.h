#ifndef DUNGEON_PLAYER_OBJECT_ACTION_STATE_H
#define DUNGEON_PLAYER_OBJECT_ACTION_STATE_H

#include "common.h"

struct EntityRec;

/* Dungeon action blocking predicate. */
s32 is_dungeon_action_blocked(void);
s32 has_pending_dungeon_activity(void *unused_actor);
s32 has_pending_actor_or_turn_action(void *unused_actor);
s32 has_actor_or_actions(void *unused_actor);

#endif
