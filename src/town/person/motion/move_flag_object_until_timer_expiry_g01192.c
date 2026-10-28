/* Move flag object until timer expiry.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01192 - CL:town/func_800CF814.
 */
#include "town/person/motion/move_flag_object_until_timer_expiry_g01192.h"

/* Moves the object by fixed steps until its timer expires, then advances the state. */
void move_flag_object_until_timer_expiry(TownCf814State *motion, TownCf814Obj *target, s32 unused, s32 duration, s32 step_x, s32 step_y) {
    TownCf814Obj *obj = target;
    s32 initial_dx = step_x;
    s16 phase = motion->unk6A;
    s32 initial_dy = step_y;
    u16 timer;

    switch (phase) {
    case 0:
        motion->unk6C = duration;
        obj->unkE = initial_dx;
        obj->unk12 = initial_dy;
        motion->unk6A++;
        break;
    case 1:
        break;
    default:
        return;
    }

    timer = motion->unk6C - 1;
    initial_dx = timer;
    initial_dy = timer;
    motion->unk6C = timer;
    if ((timer << 0x10) > 0) {
        obj->unk2 += obj->unkE;
        obj->unk6 += obj->unk12;
    } else {
        motion->unk6A = 0;
        motion->unk68++;
    }
}

/* Calls move_flag_object_until_timer_expiry with state_addr, object_addr, unused, 0x20, 0, - 4. */
void run_32_tick_movement_phase(TownCf814State *state_addr, TownCf814Obj *object_addr, s32 unused) {
    move_flag_object_until_timer_expiry(state_addr, object_addr, unused, 0x20, 0, -4);
}

/* Forward three inputs with fixed parameters 16, -4, and 8. */
void move_flag_object_by_step_16_minus_4_plus_8(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third) {
    move_flag_object_until_timer_expiry(input_first, input_second, input_third, 0x10, -4, 8);
}

/* Forward three inputs with fixed parameters 16, 8, and -4. */
void move_flag_object_by_step_16_plus_8_minus_4(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third) {
    move_flag_object_until_timer_expiry(input_first, input_second, input_third, 16, 8, -4);
}

/* Advance the object's timed movement with duration 16 and step (-8, 0). */
void move_flag_object_by_step_16_minus_8(TownCf814State *state, TownCf814Obj *obj, s32 unused) {
    move_flag_object_until_timer_expiry(state, obj, unused, 0x10, -8, 0);
}

/* Forward three inputs with fixed parameters 16, 8, and 4. */
void move_flag_object_by_step_16_plus_8_plus_4(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third) {
    move_flag_object_until_timer_expiry(input_first, input_second, input_third, 16, 8, 4);
}

/* Forward three inputs with fixed parameters 16, -4, and -8. */
void move_flag_object_by_step_16_minus_4_minus_8(TownCf814State *input_first, TownCf814Obj *input_second, s32 input_third) {
    move_flag_object_until_timer_expiry(input_first, input_second, input_third, 0x10, -4, -8);
}

/* Update object movement with a 32-tick duration and a positive Y step of 4. */
void move_flag_object_by_step_32_plus_y_4(TownCf814State *state, TownCf814Obj *object, s32 unused) {
    move_flag_object_until_timer_expiry(state, object, unused, 0x20, 0, 4);
}
