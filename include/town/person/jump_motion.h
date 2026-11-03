#ifndef TOWN_PERSON_JUMP_MOTION_H
#define TOWN_PERSON_JUMP_MOTION_H

#include "common.h"
#include "shared/town_object.h"

struct S_800CC070_1;

void set_initial_jump_velocity(TownObjectRecord *jump_state, struct S_800CC070_1 *body, void *context);
void update_jump_motion(TownObjectRecord *actor, struct S_800CC070_1 *motion, void *animation_id, s16 jump_velocity);
void invoke_state_indexed_callback(void *object, void *context, void *motion);

#endif
