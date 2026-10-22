#ifndef TOWN_PERSON_MOTION_MOVE_FLAG_OBJECT_UNTIL_TIMER_EXPIRY_G01192_H
#define TOWN_PERSON_MOTION_MOVE_FLAG_OBJECT_UNTIL_TIMER_EXPIRY_G01192_H
/* Move flag object until timer expiry. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01192 - CL:town/func_800CF814. */

#include "common.h"

typedef struct {
    u8 pad0[0x68];
    u16 unk68;
    s16 unk6A;
    u16 unk6C;
} TownCf814State;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[6];
    u16 unkE;
    u8 pad10[2];
    u16 unk12;
} TownCf814Obj;

/* Functions defined in this translation unit. */
void move_flag_object_until_timer_expiry(TownCf814State *motion, TownCf814Obj *target, s32 unused, s32 duration, s32 step_x, s32 step_y);
void run_32_tick_movement_phase(s32 state_addr, s32 object_addr, s32 unused);
void move_flag_object_by_step_16_minus_4_plus_8(s32 input_first, s32 input_second, s32 input_third);
void move_flag_object_by_step_16_plus_8_minus_4(s32 input_first, s32 input_second, s32 input_third);
void move_flag_object_by_step_16_minus_8(s32 state, s32 obj, s32 unused);
void move_flag_object_by_step_16_plus_8_plus_4(s32 input_first, s32 input_second, s32 input_third);
void move_flag_object_by_step_16_minus_4_minus_8(s32 input_first, s32 input_second, s32 input_third);
void move_flag_object_by_step_32_plus_y_4(s32 state, s32 object, s32 unused);

#endif
