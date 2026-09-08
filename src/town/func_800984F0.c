#include "common.h"

extern s16 func_8008C6B8(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_800D041C;

/* Call func_8008C6B8 with the input, D_800D041C, and parameter. */
s16 func_80095C50(s32 input_value, s32 parameter) {
    return func_8008C6B8(input_value, D_800D041C, parameter);
}
