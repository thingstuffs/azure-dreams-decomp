#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[];
extern u8 D_800C81E4[];
extern u8 D_800D6110[];

void func_800C8248(void *arg0, s32 arg1, s32 arg2) {
    *(s32 *)((u8 *)arg0 + 0xA0) = 0;
    func_800C2E84(arg0, arg2, D_800D6110);
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60) * 8] = 0;
    *(void **)((u8 *)arg0 + 0x54) = D_800C81E4;
    *(s16 *)((u8 *)arg0 + 0x6C) = 0x62;
}
