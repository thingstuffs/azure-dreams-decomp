#include "common.h"

extern void move_flag_object_until_timer_expiry(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* Forward three inputs with fixed parameters 16, -4, and 8. */
void move_flag_object_by_step_16_minus_4_plus_8(s32 input_first, s32 input_second, s32 input_third) {
    move_flag_object_until_timer_expiry(input_first, input_second, input_third, 0x10, -4, 8);
}
