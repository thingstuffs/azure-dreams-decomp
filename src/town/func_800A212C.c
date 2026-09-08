#include "common.h"

extern s32 func_8009F77C(s32, s32);
extern s32 func_8009F830();

s32 func_8009F88C(s32 arg0, s32 arg1) {
    s32 var_s0;

    var_s0 = 0;
    if (func_8009F77C(arg0, arg1) != 0) {
        var_s0 = 1;
    } else if (func_8009F830(arg0, arg1) != 0) {
        var_s0 = 1;
    }
    return var_s0;
}
