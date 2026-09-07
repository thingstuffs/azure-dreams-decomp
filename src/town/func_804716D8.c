#include "common.h"

s32 func_8001A7B0(s32);

s32 func_800186D8(void) {
    if (func_8001A7B0(3) != 0) {
        return 2;
    }
    return func_8001A7B0(2) != 0;
}
