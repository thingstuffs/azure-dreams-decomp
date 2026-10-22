#ifndef DUNGEON_MONSTER_TROLL_H
#define DUNGEON_MONSTER_TROLL_H

/* Function contracts owned by src/dungeon/monster/troll/ (decision 74; maintained by tools/headers). */
#include "common.h"
s32 check_and_prepare_actor_move(void *action_state, s32 facing, void *origin, void *actor);
void prepare_actor_path_movement(void *action_input, s32 x_offset_input, void *position_input, void *actor_input);
void select_and_advance_actor_move(u8 *move_input, void *action_context, u8 *position, u8 *actor);


#endif
