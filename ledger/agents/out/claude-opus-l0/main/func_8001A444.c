#include "common.h"

extern s32 func_8007C9C8(s32 arg0);

extern s32 D_80409270[];
extern s32 D_80409274[];
extern s32 D_80409278[];
extern s32 D_8040927C[];

s32 func_80401444(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_8007C9C8(D_80409270[0]) != 0) {
        var_v0 = 1;
        goto done;
    }
    if (func_8007C9C8(D_80409274[0]) != 0) {
        var_v0 = 2;
        goto done;
    }
    if (func_8007C9C8(D_80409278[0]) != 0) {
        var_v0 = 3;
        goto done;
    }
    if (func_8007C9C8(D_8040927C[0]) != 0) {
        var_v0 = 4;
    }
done:
    return var_v0;
}
