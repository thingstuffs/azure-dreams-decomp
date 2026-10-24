#ifndef TOWN_PERSON_JUMP_MOTION_H
#define TOWN_PERSON_JUMP_MOTION_H

#include "common.h"

struct S_800CC070_0;
struct S_800CC070_1;

void set_initial_jump_velocity(struct S_800CC070_0 *jump_state, struct S_800CC070_1 *body, void *context);
void update_jump_motion(struct S_800CC070_0 *actor, struct S_800CC070_1 *motion, void *animation_id, s16 jump_velocity);
void invoke_state_indexed_callback(void *object, void *context, void *motion);

#endif
