#include "common.h"

extern s8 D_800CF720[16];

s32 func_8008AD1C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_result;
    s32 var_a3;
    s32 var_v0;
    s32 var_t1;
    s8 *var_t0;
    s8 *var_v1;

    var_t0 = D_800CF720;
    var_a3 = 0;
    var_v0 = -1;
    if (var_t0[1] != var_v0) {
        var_t1 = var_v0;
        var_v1 = var_t0;
loop_2:
        if ((arg0 != var_v1[0]) || (arg1 != var_v1[1]) || (arg2 != *(s16 *)(var_v1 + 2))) {
            var_v1 += 8;
            var_a3 += 1;
            if (var_v1[1] == var_t1) {
                goto block_6;
            }
            goto loop_2;
        }
        var_result = var_a3;
    } else {
block_6:
        var_result = var_a3 - 0x80000000;
    }
    ASM_USE(var_result);   /* MATCH pin: retail branch polarity depends on it */
    return var_result;
}
