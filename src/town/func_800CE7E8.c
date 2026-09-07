#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern u8 D_80082660[];
extern u8 D_800CBFAC[];
extern u8 D_800D6A70[];

void func_800CBF48(void *arg0, s32 arg1, s32 arg2) {
    func_800C2E84(arg0, arg2, D_800D6A70);
    D_80082660[*(s32 *)((u8 *)arg0 + 0x60) * 8] = 0;
    *(s16 *)((u8 *)arg0 + 0x68) = 0;
    *(s16 *)((u8 *)arg0 + 0x6A) = 0;
    *(void **)((u8 *)arg0 + 0x54) = D_800CBFAC;
    *(s16 *)((u8 *)arg0 + 0x6C) = 0;
}
