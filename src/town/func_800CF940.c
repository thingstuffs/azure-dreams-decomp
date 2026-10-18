#include "common.h"

extern void move_flag_object_until_timer_expiry(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Advance the object's timed movement with duration 16 and step (-8, 0). */
void move_flag_object_by_step_16_minus_8(s32 state, s32 obj, s32 unused) {
    move_flag_object_until_timer_expiry(state, obj, unused, 0x10, -8, 0);
}
