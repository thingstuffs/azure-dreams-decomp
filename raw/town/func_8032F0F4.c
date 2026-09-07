#include "common.h"

extern s32 func_800194E4(s32 arg0, s32 arg1);
extern void func_80019860(s32 arg0, s32 arg1, s32 arg2);

void func_800198F4(s32 arg0, void *arg1, s32 arg2) {
    void *temp_v0;

    temp_v0 = (void *)((*(s16 *)(arg0 + (func_800194E4(arg0, arg2) * 8) + 2) * 8) + *(s32 *)((u8 *)arg1 + 0x14));
    func_80019860(*(s16 *)((u8 *)temp_v0 + 0), *(s16 *)((u8 *)temp_v0 + 2), *(s16 *)((u8 *)temp_v0 + 4));
}
