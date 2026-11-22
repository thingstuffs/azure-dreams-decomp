#ifndef TOWN_PERSON_JUMP_MOTION_H
#define TOWN_PERSON_JUMP_MOTION_H

#include "common.h"
#include "shared/town_object.h"

struct S_800CC070_1;

void set_initial_jump_velocity(TownObjectRecord *jump_state, struct S_800CC070_1 *body, struct SpriteFrameState *sprite);
void update_jump_motion(TownObjectRecord *actor, struct S_800CC070_1 *motion, struct SpriteFrameState *sprite, s16 jump_velocity);
void move_flag_object_with_step_minus_10(TownObjectRecord *object, s32 motion, struct SpriteFrameState *sprite);
void move_flag_object_with_step_minus_15(TownObjectRecord *object, s32 motion, struct SpriteFrameState *sprite);
void invoke_state_indexed_callback(TownObjectRecord *object, struct ObjectPosition *position, struct SpriteFrameState *sprite);

#endif
