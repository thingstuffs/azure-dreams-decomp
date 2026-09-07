#include "common.h"

extern void func_80401BF4(void *arg0, s32 arg1);
extern s32 func_80401C70(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_80401D28(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_80401FEC(void *arg0);
extern void func_804021F4(void);
extern void func_8007BF18(void *arg0);
extern u8 D_8009DDD8[];
extern u8 D_80400138[];

s32 func_8001B154(s32 arg0, void *arg1) {
    u8 sp18[32];
    s32 result;

    func_80401BF4(sp18, arg0);
    result = func_80401C70(sp18, arg1, 0xC0, 0);
    if (result != 0) {
        result = func_80401FEC(arg1);
        if (result != 0) {
            result = func_80401D28(sp18, D_8009DDD8 + (arg0 << 7), 1, 4,
                                   *(s32 *)(D_8009DDD8 + (arg0 << 7)));
            func_804021F4();
        }
        func_8007BF18(D_80400138);
    }
    return result;
}
