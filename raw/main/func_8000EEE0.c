#include "common.h"

s32 func_80021EE0(void *arg0) {
    s32 *var_a1;
    s32 var_a2;
    s32 var_v1;

    var_a2 = 0;
    var_a1 = (s32 *) ((u8 *) arg0 + 0x208);
    var_v1 = var_a2;
    do {
        var_a2 ^= *var_a1++;
        var_v1 += 1;
    } while (var_v1 < 6014);
    return (*(s32 *) ((u8 *) arg0 + 0x204) ^ var_a2) == 0;
}
