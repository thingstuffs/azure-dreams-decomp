#include "common.h"

extern s32 func_800AC82C(void);
extern s32 func_800AD9B4(void *, void *);
extern void func_80047784(void *, u8, s32);
extern void func_801708B8(void *, s32, void *);

extern s16 D_80083228[];
extern u8 D_800E23E0[];
extern u8 D_800E2428[];
extern u8 D_80171A80[];

void func_80174A68(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    if (func_800AC82C() != 0) {
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            *(void **)((u8 *)arg0 + 0x8C) = D_80171A80;
            return;
        }
    } else if (*(void **)((u8 *)arg2 + 0x2C) == D_800E2428 &&
               !(*(s32 *)((u8 *)arg3 + 0x1C) & 0x208)) {
        u8 *base;

        base = D_800E23E0;
        *(void **)((u8 *)arg2 + 0x2C) = base;
        func_80047784(
            arg2,
            base[((D_80083228[0] + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9) & 7],
            0);
        if (*(u8 *)((u8 *)arg0 + 0xB0) == 0) {
            func_801708B8(arg0, arg1, arg2);
        }
    }
}
