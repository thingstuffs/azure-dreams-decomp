#include "common.h"

s32 func_80019ADC();                                /* extern */

s32 func_80019AB8(void) {
    return ~func_80019ADC() != 0;
}
