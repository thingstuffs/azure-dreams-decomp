#include "common.h"

s32 func_80017E98(void *, s32);
s32 func_80019A04();
s32 func_80019ABC();
s32 func_8001A510();

extern s32 D_8001A98C;
extern s32 D_8001B1F8;
extern s32 D_8001B6D0;
extern s32 D_8001F690;
extern s8 D_8001FB7F;

s32 func_80016F64(void *arg0, s32 arg1, s32 arg2) {
    register s32 *var_s0 ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_s1;
    s32 var_v0;

    var_v0 = func_80017E98(arg0, arg1);
    var_s0 = (s32 *)0x80020000;
    if (var_v0 != 0) {
        if (func_8001A510(*(s16 *)((s8 *)arg0 + 0x18)) == 0) {
            var_v0 = 0x80020000;
            ASM_KEEP(var_v0);   /* MATCH pin: load-bearing for the whole function shape */
            return var_v0 - 0x4930;
        }
    }

    var_s0 = (s32 *)((s8 *)var_s0 - 0x5674);
    temp_s1 = func_80019ABC(var_s0, &D_8001B1F8, arg0, arg2);
    if (func_80019A04(var_s0, arg0, arg2) != 0) {
        var_v0 = func_8001A510(*(s16 *)((s8 *)arg0 + 0x18));
        if (var_v0 == 0) {
            ASM_CLOBBER("$2");   /* MATCH pin: retail basic-block layout depends on it */
            var_v0 = 0x80020000;
            ASM_KEEP(var_v0);   /* MATCH pin: load-bearing for the whole function shape */
            temp_s1 = var_v0 - 0x970;
        } else {
            var_v0 = 0x80020000;
            ASM_KEEP(var_v0);   /* MATCH pin: load-bearing for the whole function shape */
            temp_s1 = var_v0 - 0x481;
        }
    }
    return temp_s1;
}

/* MECHANISM: Three-argument ABI holds arg0/arg2 in s2/s3 across calls.
   Guarded s0/v0 pins preserve the page-base and signed-low-half live ranges.
   The zero-path v0 clobber retains retail's redundant lui and closes the tail. */
