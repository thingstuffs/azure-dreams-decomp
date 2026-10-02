#include "common.h"

extern s32 func_800A98C4(s32 arg0);
extern s32 func_800A98F8(s32 arg0);
extern s32 func_800A9970(s32 arg0);

s32 func_800A99D8(s32 input, s32 check_value) {
    s32 result;

    if (func_800A98C4(input) != 0) {
        return 3;
    }
    if (func_800A98F8(input) != 0) {
        return 0;
    }
    result = func_800A9970(input);
    if (result != 0) {
        return 2;
    }
    return 1;
}
