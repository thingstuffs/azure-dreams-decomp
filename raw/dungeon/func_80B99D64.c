#include "common.h"

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737A4(void) __attribute__((noreturn));
extern void func_801737C4(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_80170E9C[];
extern u8 D_80174EE0[];
extern u8 D_80174F00[];

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_80173564(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    u8 *effect;
    s32 index;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return func_801737A4();

state_zero:
    {
    register u8 *global ASM_REG("$3");
    u8 *stateEffect;

    if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
        return;
    }

    global = (u8 *)&D_80083460;
    stateEffect = D_80174F00;
    FIELD(global, u16, 0xA)--;
    FIELD(arg2, void *, 0x2C) = stateEffect;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, stateEffect[index & 7], 0);
    FIELD(arg0, u8, 0x9B)++;
    return func_801737A4();
    }

state_one:
    if (FIELD(arg3, u8, 0x25) == 0) {
        if (D_80083462 & 0x1000) {
            return;
        }

        if ((FIELD(arg3, s16, 0x64) != 0) &&
            func_800AA6B4(arg0, arg1, arg2, 0)) {
            return;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            return;
        }

        {
        register void *callArg0 ASM_REG("$4") = arg0;

        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(callArg0, arg1, arg2, arg3);
            return func_801737A4();
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(callArg0, arg1, arg2, arg3);
            func_801737C4(arg0, arg1, arg2, arg3);
            return func_801737A4();
        }
        }

        if (FIELD(arg3, s8, 0x6D) == 0) {
            return;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            void *owner;

            owner = D_800814A8;
            if ((s16)func_8009A180(arg3, (u8 *)FIELD(owner, void *, 0x58) + 0x20) != 0) {
                return;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (FIELD(arg3, u8, 0x25) == 0) {
            return;
        }
    }

    effect = D_80174EE0;
    FIELD(arg2, void *, 0x2C) = effect;
    index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
    func_80047784(arg2, effect[index & 7], 0);
    FIELD(arg3, u32, 0x1C) &= ~0x200;
    FIELD(arg0, void *, 0x8C) = D_80170E9C;
}
