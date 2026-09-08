#include "common.h"

extern s32 func_800214FC();
extern void func_80021538();
extern void func_8005FE18(s32);
extern void _card_wait(s32);
extern void format(s32);
extern s32 D_80027F18[];

s32 func_80021A84(s32 arg0) {
    s32 *var_v0;
    s32 var_v1;
    s32 ret_val;

    _card_wait(0);
    _card_wait(1);
    func_80021538();
    var_v0 = &D_80027F18[0];
    if (arg0 != 0) {
        var_v0 = &D_80027F18[1];
    }
    format(*var_v0);
    do {
        var_v1 = func_800214FC();
        if (var_v1 == 0) {
            func_8005FE18(0);
        }
    } while (var_v1 == 0);
    if (var_v1 != 1) {
        if (var_v1 == 3) {
            var_v1 = 4;
        } else {
            var_v1 = 5;
        }
    }
    ret_val = var_v1;
    ASM_KEEP(ret_val);
    return ret_val;
}
