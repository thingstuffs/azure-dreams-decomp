/* Move flag object until timer expiry.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800CF814.
 */
#include "town/person/motion/move_flag_object_until_timer_expiry_g01192.h"

/* Moves the object by fixed steps until its timer expires, then advances the state. */
void move_flag_object_until_timer_expiry(TownObjectRecord *state, TownCf814Obj *target, struct SpriteFrameState *unused_sprite, s32 duration, s32 step_x, s32 step_y) {
    TownCf814Obj *obj = target;
    s32 initial_dx = step_x;
    s16 phase = state->sequence_step;
    s32 initial_dy = step_y;
    u16 timer;

    switch (phase) {
    case 0:
        state->timer = duration;
        obj->step_x = initial_dx;
        obj->step_y = initial_dy;
        state->sequence_step++;
        break;
    case 1:
        break;
    default:
        return;
    }

    timer = state->timer - 1;
    initial_dx = timer;
    initial_dy = timer;
    state->timer = timer;
    if ((timer << 0x10) > 0) {
        obj->x += obj->step_x;
        obj->y += obj->step_y;
    } else {
        state->sequence_step = 0;
        state->phase++;
    }
}

/* Calls move_flag_object_until_timer_expiry with state, position, sprite, 0x20, 0, - 4. */
void move_flag_object_toward_negative_y(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, position, sprite, 0x20, 0, -4);
}

/* Forward three inputs with fixed parameters 16, -4, and 8. */
void move_flag_object_by_step_16_minus_4_plus_8(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, position, sprite, 0x10, -4, 8);
}

/* Forward three inputs with fixed parameters 16, 8, and -4. */
void move_flag_object_by_step_16_plus_8_minus_4(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, position, sprite, 16, 8, -4);
}

/* Advance the object's timed movement with duration 16 and step (-8, 0). */
void move_flag_object_by_step_16_minus_8(TownObjectRecord *state, TownCf814Obj *obj, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, obj, sprite, 0x10, -8, 0);
}

/* Forward three inputs with fixed parameters 16, 8, and 4. */
void move_flag_object_by_step_16_plus_8_plus_4(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, position, sprite, 16, 8, 4);
}

/* Forward three inputs with fixed parameters 16, -4, and -8. */
void move_flag_object_by_step_16_minus_4_minus_8(TownObjectRecord *state, TownCf814Obj *position, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, position, sprite, 0x10, -4, -8);
}

/* Update object movement with a 32-tick duration and a positive Y step of 4. */
void move_flag_object_by_step_32_plus_y_4(TownObjectRecord *state, TownCf814Obj *object, struct SpriteFrameState *sprite) {
    move_flag_object_until_timer_expiry(state, object, sprite, 0x20, 0, 4);
}
