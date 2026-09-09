#include "common.h"

s32 func_80019ADC(s32, s32);                                /* extern */

/* Return whether func_80019ADC produces a result other than -1. */
s32 func_80019AB8(s32 first_value, s32 second_value) {
    return ~func_80019ADC(first_value, second_value) != 0;
}
