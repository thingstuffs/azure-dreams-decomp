#include "common.h"

extern s32 D_804094EC[];
extern s32 D_804000F4;
extern s32 D_80408AA0[2];
extern s8 D_80409290[];

s32 func_8007BF80();
s32 func_8007BF50();
s32 func_8007CAB8();
s32 func_8007CAC8();

s32 func_8001A9B4(void) {
    s32 sp10[8];
    s32 *var_a1;
    s8 *var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = D_80409290;
    var_a1 = &D_80408AA0[0];
    if (D_804094EC[0] != 0) {
        var_a1 = &D_80408AA0[0] + 1;
    }
    func_8007BF80(&sp10, *var_a1);
    func_8007BF50(&sp10, &D_804000F4);
    if (func_8007CAB8(&sp10, var_s0) != 0) {
        do {
            var_s1 += 1;
            var_s0 += 0x28;
        } while (func_8007CAC8(var_s0) == var_s0);
    }
    return var_s1;
}
