#include "common.h"
#include "m2c_compat.h"

s32 func_800175B0();                                /* extern */
s32 func_80017620(s32);                             /* extern */
s32 func_8001764C();                                /* extern */
s32 func_800176D4();                                /* extern */
extern s32 D_80019BB0;
extern s32 D_80019BB4;

s32 func_800178B4(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;

    D_80019BB0 = 2;
    var_v0 = 1;
    if (func_800175B0() != 0) {
        var_s0 = func_8001764C();
        if (var_s0 == 0) {
            var_s0 = func_800176D4();
        }
        temp_v0 = func_80017620(var_s0);
        D_80019BB4 = var_s0;
        M2C_FIELD(((arg1 * 0x10) + M2C_FIELD(arg0, s32 *, 0x10)), s32 *, 8) = temp_v0;
        var_v0 = 0;
    }
    return var_v0;
}
