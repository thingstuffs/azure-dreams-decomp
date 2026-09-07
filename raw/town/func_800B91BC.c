#include "common.h"

extern void func_800B67A4(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_800B683C(void *arg0);
extern void func_800B68C8(void *arg0, s32 arg1, s32 arg2);

void func_800B691C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_800B67A4((u8 *)arg0 + 0x88, (u8 *)arg0 + 0x60, (u8 *)arg0 + 0x70, arg3, arg4, arg5);
    func_800B683C(arg0);
    func_800B68C8(arg0, arg1, arg2);
}
