#include "common.h"

extern s32 D_804094EC[];
extern s32 D_80408AA0[2];
extern s32 D_80408AA8[];
extern s32 D_80408AB8[];

s32 func_8007BF80();
s32 func_8007BF50();

void func_8001ABF4(s32 arg0, s32 arg1) {
    s32 *var_a1;

    var_a1 = &D_80408AA0[0];
    if (D_804094EC[0] != 0) {
        var_a1 = &D_80408AA0[0] + 1;
    }
    func_8007BF80(arg0, *var_a1);
    func_8007BF50(arg0, &D_80408AA8[0]);
    func_8007BF50(arg0, D_80408AB8[arg1]);
}
