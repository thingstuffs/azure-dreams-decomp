#include "common.h"

extern s32 func_800194D8();

s32 func_805D376C(void) {
    s32 index;
    index = 1;
    while (func_800194D8(index + 0x147A) != 0) {
        index += 1;
        if (index >= 0x10) {
            break;
        }
    }
    return index == 0x10;
}
