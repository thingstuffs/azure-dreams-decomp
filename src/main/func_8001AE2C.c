#include "common.h"

extern void func_80401BF4(void *arg0, s32 arg1);
extern s32 func_80401AA4(s32 arg0, void *arg1);
extern s32 func_80401C70(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 D_804094EC[];
extern s32 D_80136140[];
extern u8 D_8009DDD8[];

s32 func_8001AE2C(s32 arg0) {
    u8 sp10[32];
    s32 *var_a0;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 1;
    func_80401BF4(sp10, arg0);
    if (D_804094EC[0] != 0) {
        var_a0 = D_80136140 + 1;
    } else {
        var_a0 = D_80136140;
    }
    temp_s0 = arg0 << 7;
    temp_v0 = func_80401AA4(*var_a0, &sp10[5]);
    *(s32 *)(D_8009DDD8 + temp_s0) = temp_v0;
    if (temp_v0 != 0) {
        var_s1 = func_80401C70(sp10, D_8009DDD8 + temp_s0, 1, 4);
        *(s32 *)(D_8009DDD8 + temp_s0) = 1;
    }
    return var_s1;
}
