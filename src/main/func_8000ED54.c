#include "common.h"

extern void func_80021B18(void *arg0, s32 arg1);
extern s32 func_80021A04(s32 arg0, void *arg1);
extern s32 func_80021B98(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 D_800287CC;
extern s32 D_80084128[];
extern s32 D_80083E98[];

s32 func_80021D54(s32 arg0) {
    s32 sp10[8];
    s32 *var_v0;
    u8 *base;
    s32 *temp_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 1;
    func_80021B18(sp10, arg0);
    var_v0 = &D_80084128[0];
    if (D_800287CC != 0) {
        var_v0 = &D_80084128[1];
    }
    temp_v0 = func_80021A04(*var_v0, (u8 *)sp10 + 5);
    base = (u8 *)D_80083E98;
    temp_s0 = (s32 *)(base + (arg0 << 7));
    *temp_s0 = temp_v0;
    if (temp_v0 != 0) {
        var_s1 = func_80021B98(sp10, temp_s0, 1, 4);
        *temp_s0 = 1;
    }
    return var_s1;
}
