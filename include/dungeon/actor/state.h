#ifndef DUNGEON_ACTOR_STATE_H
#define DUNGEON_ACTOR_STATE_H

/* Function contracts owned by src/dungeon/actor/state/ (decision 74; maintained by tools/headers). */
#include "common.h"

struct SpriteFrameState;
struct ActorRecord;
void create_default_state_object(s16 new_state);
void set_actor_action_state_eight(void *record_data, void *unused_position, void *unused_context);

s32 resolve_actor_floor_trap_once(void *action, s32 unused, void *source, void *target);
struct S_800D491C_0;
void set_actor_data_pointer(struct S_800D491C_0 *object, s32 context, void *source, void *target);

s32 propagate_actor_action_flag(void *unused_0, s32 unused_1, s32 unused_2, s32 *record);
void install_trap_handler_after_action_flag_propagation(void *owner, s32 context, s32 sprite, s32 *record);


void roll_actor_flag_once(void *actor_data, s32 divisor);

void initialize_action_state_29(void *state, s32 unused_context, struct SpriteFrameState *unused_sprite, struct ActorRecord *unused_actor);

void reset_record_to_state_34(void *state, s32 unused_context, struct SpriteFrameState *unused_sprite, struct ActorRecord *unused_actor);

#endif
