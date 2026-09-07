#include "common.h"

extern u32 D_800814A0[3];
extern void func_800478B8(void *arg0);
extern void func_80047784(void *arg0, s32 arg1, s32 arg2);

void func_801751C4(u16 *arg0, u32 *arg1, u16 *arg2) {
    s32 temp_v0;
    s32 temp_a1;
    s32 var_v0;

    temp_v0 = arg0[0] + 1;
    arg0[0] = temp_v0;
    temp_v0 = temp_v0 << 16;
    temp_a1 = temp_v0 >> 16;
    if (temp_a1 >= 8) {
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (temp_a1 >= 6) {
        s32 temp_a1_2;
        temp_a1_2 = temp_a1 + 6;
        temp_a1 = ((s16 *)arg0)[2] + temp_a1_2;
        var_v0 = temp_a1;
        if (temp_a1 < 0) {
            var_v0 = temp_a1 + 7;
        }
        arg2[9] = arg0[3] + (temp_a1 - ((var_v0 >> 3) << 3)) + 8;
    } else {
        s32 temp_a1_2;
        temp_a1_2 = temp_a1 + 6;
        temp_a1 = ((s16 *)arg0)[2] + temp_a1_2;
        var_v0 = temp_a1;
        if (temp_a1 < 0) {
            var_v0 = temp_a1 + 7;
        }
        arg2[9] = arg0[3] + (temp_a1 - ((var_v0 >> 3) << 3));
        arg1[0] += arg1[3];
        arg1[1] += arg1[4];
    }
    func_800478B8(arg2);
    if (arg2[10] & 0x6000) {
        func_80047784(arg2, 0x30, 0);
    }
}
