#ifndef TOWN_PERSON_MOTION_MOVE_FLAG_OBJECT_UNTIL_TIMER_EXPIRY_G01192_H
#define TOWN_PERSON_MOTION_MOVE_FLAG_OBJECT_UNTIL_TIMER_EXPIRY_G01192_H
/* Move flag object until timer expiry. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800CF814. */

#include "common.h"

#include "shared/town_object.h"

/* Integer-half position/step view of the town object moved by the phase helper.
 * move_flag_object_until_timer_expiry installs per-tick steps and advances these coordinates. */
typedef struct {
    u8 pad0[2];
    u16 x; /* integer X coordinate, increased by unkE each active movement tick */
    u8 pad4[2];
    u16 y; /* integer Y coordinate, increased by unk12 each active movement tick */
    u8 pad8[6];
    u16 step_x; /* X step per movement tick, copied from the step_x argument */
    u8 pad10[2];
    u16 step_y; /* Y step per movement tick, copied from the step_y argument */
} TownCf814Obj;

/* Functions defined in this translation unit. */
void move_flag_object_until_timer_expiry(TownObjectRecord *state, TownCf814Obj *target, struct SpriteFrameState *unused_sprite, s32 duration, s32 step_x, s32 step_y);
void move_flag_object_toward_negative_y(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite);
void move_flag_object_by_step_16_minus_4_plus_8(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite);
void move_flag_object_by_step_16_plus_8_minus_4(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite);
void move_flag_object_by_step_16_minus_8(TownObjectRecord *state, TownCf814Obj *obj, struct SpriteFrameState *sprite);
void move_flag_object_by_step_16_plus_8_plus_4(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite);
void move_flag_object_by_step_16_minus_4_minus_8(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite);
void move_flag_object_by_step_32_plus_y_4(TownObjectRecord *state, TownCf814Obj *object, struct SpriteFrameState *sprite);

#endif
