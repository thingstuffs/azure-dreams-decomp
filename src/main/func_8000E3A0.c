#include "common.h"

extern struct {
    s32 v;
    s32 pad[2];
} D_800287C8;

s32 func_800213A0(void) {
    s32 var_v1;

    var_v1 = 0;
    if (D_800287C8.v != 0) {
        var_v1 = 5;
        D_800287C8.v = 0;
    }
    return var_v1;
}
