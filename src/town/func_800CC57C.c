#include "common.h"

extern void func_800C2E84(void *, s32, void *);
extern s32 func_800374F4(s32);
extern u8 D_800C9AD4[];
extern u8 D_800D6504[];

void func_800C9CDC(void *arg0, void *arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, D_800D6504);
    *(void **)((u8 *)arg0 + 0x50) = D_800C9AD4;
    *(s32 *)((u8 *)arg1 + 0x14) = 0xFFF60000;
    *(s16 *)((u8 *)arg0 + 0x90) = (s16)(func_800374F4(3) + 1);
}
