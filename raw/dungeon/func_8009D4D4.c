#include "common.h"

extern u32 D_80083460[];

s32 func_800A2C34(void) {
    u32 *var_v1;

    var_v1 = D_80083460;
    if (var_v1[3] != 0 || var_v1[4] != 0 || *(s16 *)((s8 *)var_v1 + 0xA) != 0) {
        return 1;
    }
    return 0;
}
