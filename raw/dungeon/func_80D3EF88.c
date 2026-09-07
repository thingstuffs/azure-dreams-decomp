#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784();
extern s32 func_8009A180();
extern s32 func_800A2C34();
extern void func_800A9A04();
extern void func_800A9A0C();
extern void func_800AA258();
extern s32 func_800AA6B4();
extern void func_800AA888();
extern void func_80174A68();

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_800E2428[];
extern u8 D_800E2430[];
extern u8 D_80171A80[];

void func_80174788(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 state;
    u16 old_value;
    u16 current_value;
    s32 flags;
    u8 *global_base;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base;

        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA)--;
    }
    FIELD(arg2, void *, 0x2C) = D_800E2428;
    func_80047784(arg2,
                  D_800E2428[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
    goto increment_state;

state_one:
    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, u16, 2) & 0x1000) {
        goto done;
    }
    if (FIELD(arg3, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }
    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x100) {
        func_800AA258(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, arg1, arg2, arg3);
        current_value = FIELD(arg0, u16, 0x92);
        old_value = FIELD(arg0, u16, 0xA2);
        FIELD(arg0, u16, 0xA2) = 0;
        FIELD(arg0, s16, 0x9E) = 0;
        FIELD(arg0, u16, 0x92) = current_value - old_value;
        func_80174A68(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(arg3, FIELD(D_800814A8, s32, 0x58) + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if (FIELD(arg3, u8, 0x25) == 0) {
        goto done;
    }
    FIELD(arg2, void *, 0x2C) = D_800E2430;
    func_80047784(arg2,
                  D_800E2430[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                  0);
    FIELD(arg3, s32, 0x1C) |= 0x40000;
    FIELD(global_base, u16, 0xA)++;

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    {
        u8 *counter_base2;

        counter_base2 = (u8 *)&D_80083460;
        FIELD(counter_base2, u16, 0xA)--;
    }
    FIELD(arg3, s32, 0x1C) &= ~8;
    FIELD(arg0, void *, 0x8C) = D_80171A80;

done:
    return;
}
