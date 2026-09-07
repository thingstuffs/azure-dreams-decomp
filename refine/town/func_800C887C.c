#include "common.h"

extern void func_800C2E84(void *arg0, s32 arg1, void *arg2);
extern void func_800C4174(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80082660[];
extern u8 D_800D5518[];
extern u8 D_800D55A0[];
extern u8 D_800D55A8[];
extern u8 D_800D55D0[];
extern u8 D_800D55D4[];

/* Resets menu state and switches handlers when the input flags request it. */
void func_800C5FDC(void *menu, s32 update_arg, void *input) {
    if (*(u16 *)((u8 *)input + 0x14) & 0x6000) {
        func_800C2E84(menu, (s32)input, D_800D5518);
        D_80082660[(*(s32 *)((u8 *)menu + 0x60)) * 8] = 0;
        *(void **)((u8 *)menu + 0x58) = D_800D55D0;
        *(void **)((u8 *)menu + 0x5C) = D_800D55D4;
        *(void **)((u8 *)menu + 0x7C) = D_800D55A0;
        *(void **)((u8 *)menu + 0x80) = D_800D55A8;
        *(u8 *)((u8 *)menu + 0x70) = 0;
        func_800C4174(menu, update_arg, (s32)input);
    }
}
