#include "common.h"

extern s32 func_800352FC(void);
extern s32 func_800C2A60(void *arg0);
extern void func_800C3158(void);
extern void func_800C40D0(void *arg0, s32 arg1, s32 arg2);
extern void func_800C4134(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80082A39[16];

s32 func_800C30E0(void *arg0, s32 arg1, s32 arg2) {
    if (func_800352FC() == 0) {
        return 0;
    }

    if (func_800C2A60(arg0) != 0 ||
        D_80082A39[0] == *(s32 *)((u8 *)arg0 + 0x60)) {
        func_800C40D0(arg0, arg1, arg2);
        return 1;
    }

    func_800C4134(arg0, arg1, arg2);
    return 1;
}
