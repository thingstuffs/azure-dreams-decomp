#include "common.h"
void blit_default_rectangle(s32, s32, s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */                            /* extern */

/* Forward four values to blit_default_rectangle and return zero. */
s32 forward_four_values_and_return_zero(s32 first_value, s32 second_value, s32 third_value, s32 fourth_value) {
    blit_default_rectangle(first_value, second_value, third_value, fourth_value);
    return 0;
}
