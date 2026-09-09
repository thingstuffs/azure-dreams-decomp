#include "common.h"

s32 func_80019ADC(s32, s32);                                /* extern */

s32 func_80019AB8(s32 arg0, s32 arg1) {
    return ~func_80019ADC(arg0, arg1) != 0;
}
