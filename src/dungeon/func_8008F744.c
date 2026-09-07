#include "common.h"

extern s32 D_80083168[4];

s32 func_80094EA4(void) {
    if (!(D_80083168[0] & 0x10)) {
        if (D_80083168[0] & 0xF0A3) {
            return 1;
        }
    }
    return 0;
}
