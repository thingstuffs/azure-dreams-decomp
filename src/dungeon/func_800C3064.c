#include "common.h"

extern void func_80099844(void *arg0, const void *arg1);
extern s32 func_800C8844(void *arg0, s16 arg1, s16 arg2);
extern void func_800DC1B8(s32 arg0);

extern s32 D_800DCF1C[];
extern u8 D_800E19C2[];
extern u8 D_800E19D3[];

s32 func_800C87C4(void *arg0, s16 arg1, s16 arg2) {
    if (func_800C8844(arg0, arg1, arg2) != 0) {
        func_80099844(arg0, D_800E19C2);
        if (*(u8 *)((u8 *)arg0 + 0x13) == 0) {
            func_800DC1B8(D_800DCF1C[0]);
        }
        return 1;
    }

    func_80099844(arg0, D_800E19D3);
    return 0;
}
