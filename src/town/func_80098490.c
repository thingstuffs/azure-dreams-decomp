#include "common.h"

extern s16 func_8008C570(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D0414;

/* Call func_8008C570 with the input, D_800D0414, and parameter. */
s16 func_80095BF0(s32 input_value, s32 parameter) {
    return func_8008C570(input_value, D_800D0414, parameter);
}
