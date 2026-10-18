#include "common.h"

extern void move_flag_object_until_timer_expiry(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Update object movement with a 32-tick duration and a positive Y step of 4. */
void move_flag_object_by_step_32_plus_y_4(s32 state, s32 object, s32 unused) {
    move_flag_object_until_timer_expiry(state, object, unused, 0x20, 0, 4);
}
