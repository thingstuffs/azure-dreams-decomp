#include "common.h"

extern s32 D_800C3960;
s16 func_800C2BE8(void *arg0);
void func_800C4174(void *arg0, s32 arg1, s32 arg2);

void func_800C40D0(void *arg0, s32 arg1, s32 arg2) {
    *(s8 *)((u8 *)arg0 + 0x15) = 0;
    *(void **)((u8 *)arg0 + 0x50) = &D_800C3960;
    *(s16 *)((u8 *)arg0 + 0x72) = func_800C2BE8(arg0);
    func_800C4174(arg0, arg1, arg2);
}
