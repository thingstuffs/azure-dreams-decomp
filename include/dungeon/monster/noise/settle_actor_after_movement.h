#include "shared/entity.h"
#ifndef DUNGEON_OVL_7F43F800_P04_H
#define DUNGEON_OVL_7F43F800_P04_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"








// Initializes the state and applies a table entry selected by the combined source and global index.
struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern void func_80047784(void *, s16, s16);
extern u8 D_80174EA0[9];
void settle_actor_after_movement(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *context, ActorRecord *source);
#endif
