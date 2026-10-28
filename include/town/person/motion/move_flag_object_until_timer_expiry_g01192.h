#ifndef TOWN_PERSON_MOTION_MOVE_FLAG_OBJECT_UNTIL_TIMER_EXPIRY_G01192_H
#define TOWN_PERSON_MOTION_MOVE_FLAG_OBJECT_UNTIL_TIMER_EXPIRY_G01192_H
/* Move flag object until timer expiry. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01192 - CL:town/func_800CF814. */

#include "common.h"

/* Timed movement phase state supplied by the town actor caller.
 * move_flag_object_until_timer_expiry initializes the timer and advances the outer phase on expiry. */
typedef struct {
    u8 pad0[0x68];
    u16 unk68; /* outer movement phase; incremented when the timer expires */
    s16 unk6A; /* movement subphase: 0 initializes the timer/steps, 1 continues them */
    u16 unk6C; /* remaining movement callback ticks; decremented before each movement step */
} TownCf814State;

/* Integer-half position/step view of the town object moved by the phase helper.
 * move_flag_object_until_timer_expiry installs per-tick steps and advances these coordinates. */
typedef struct {
    u8 pad0[2];
    u16 unk2; /* integer X coordinate, increased by unkE each active movement tick */
    u8 pad4[2];
    u16 unk6; /* integer Y coordinate, increased by unk12 each active movement tick */
    u8 pad8[6];
    u16 unkE; /* X step per movement tick, copied from the step_x argument */
    u8 pad10[2];
    u16 unk12; /* Y step per movement tick, copied from the step_y argument */
} TownCf814Obj;

/* Functions defined in this translation unit. */
void move_flag_object_until_timer_expiry(TownCf814State *motion, TownCf814Obj *target, s32 unused, s32 duration, s32 step_x, s32 step_y);
void run_32_tick_movement_phase(TownCf814State *state_addr, TownCf814Obj *object_addr, s32 unused);
void move_flag_object_by_step_16_minus_4_plus_8(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third);
void move_flag_object_by_step_16_plus_8_minus_4(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third);
void move_flag_object_by_step_16_minus_8(TownCf814State *state, TownCf814Obj *obj, s32 unused);
void move_flag_object_by_step_16_plus_8_plus_4(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third);
void move_flag_object_by_step_16_minus_4_minus_8(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third);
void move_flag_object_by_step_32_plus_y_4(TownCf814State *state, TownCf814Obj *object, s32 unused);

#endif
