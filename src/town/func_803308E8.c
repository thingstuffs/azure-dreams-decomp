#include "common.h"

extern s32 func_8001ADE0(s32);

s32 func_8001B0E8(s32 arg0, s32 arg1) {
    s32 i;
    s32 result;

    i = 0;
    result = 0;
    if (arg1 > 0) {
        do {
            if (func_8001ADE0(arg0 + i) != 0) {
                result += 1 << i;
            }
            i++;
        } while (i < arg1);
    }
    return result;
}
