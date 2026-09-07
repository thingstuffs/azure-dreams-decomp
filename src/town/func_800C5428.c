#include "common.h"

extern s16 func_80065F90(s32, s32, s32, s32);

s16 func_800C2B88(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 minimum;
    register s32 var_a3 ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    var_a3 = (s32)0x80010000;
    arg0 <<= 16;
    ASM_KEEP(var_a3);   /* MATCH pin: retail immediate-load split depends on it */
    temp_a0 = arg0 - *(s32 *)((u8 *)arg2 + 0);
    temp_v1 = (arg1 << 16) - *(s32 *)((u8 *)arg2 + 4);
    minimum = var_a3;
    if (temp_a0 > minimum) {
        var_a3 = temp_a0;
    }
    var_a1 = (s32)0x80010000;
    if (temp_v1 > minimum) {
        var_a1 = temp_v1;
    }
    return func_80065F90(var_a3, var_a1, minimum, var_a3);
}
