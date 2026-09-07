#include "common.h"

#include "common.h"

extern void func_8004D12C(void *);

void func_8004D1EC(void *arg0, u16 *arg1, s32 arg2, u16 *arg3) {
    void *state = arg0;
    s32 temp;

    *(s32 *)((s8 *)state + 0x14) = 0;
    *(s32 *)((s8 *)state + 0x1C) = 0;
    if (arg2 != 0) {
        *(s32 *)((s32)state + 0x18) = 0x400 / arg2;
    } else {
        *(s32 *)((s8 *)state + 0x18) = 0x1000;
    }
    if (arg1 != 0) {
        *(u16 *)((s8 *)state + 0xC) = arg1[0];
        *(u16 *)((s8 *)state + 0xE) = arg1[1];
        *(u16 *)((s8 *)state + 0x10) = arg1[2];
        *(s16 *)((s8 *)state + 4) = arg1[0] - arg3[0];
        *(s16 *)((s8 *)state + 6) = arg1[1] - arg3[1];
        temp = arg1[2] - arg3[2];
        *(void **)((s8 *)state + 0) = arg3;
        *(void (**)(void *))((s8 *)state - 4) = func_8004D12C;
        *(s16 *)((s8 *)state + 8) = temp;
    }
}
