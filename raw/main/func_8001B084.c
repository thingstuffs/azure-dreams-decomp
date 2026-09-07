#include "common.h"

extern void func_80401BF4(void *arg0, s32 arg1);
extern void func_8007CAD8(void *arg0, void *arg1);
extern void func_80401F98(s32 arg0);
extern s32 func_80401D28(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_80401ED4(s32 arg0, s32 arg1);
extern u8 D_8009DDD8[];

s32 func_8001B084(s32 arg0, s32 arg1) {
    u8 sp18[32];
    u8 sp38[32];
    s32 temp_s1;
    s32 temp_v0;

    func_80401BF4(sp18, arg0);
    func_80401BF4(sp38, 5);
    temp_s1 = arg0 << 7;
    if (*(s32 *)(D_8009DDD8 + temp_s1) != 0) {
        func_8007CAD8(sp18, sp38);
    }
    func_80401F98(arg1);
    temp_v0 = func_80401D28(sp38, arg1, 0xC0, 0, *(s32 *)(D_8009DDD8 + temp_s1));
    if (temp_v0 != 0) {
        func_80401ED4(arg0, arg1);
    }
    func_8007CAD8(sp38, sp18);
    return temp_v0;
}
