#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_8003AD08();
extern void func_8008D330();
extern void func_80098B38();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_80099734();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800A6D30();
extern s16 func_800AD6FC();
extern void func_800C4624();
extern void func_800C4AFC();

extern s32 D_80082E80;
extern u16 D_80083460[];
extern s32 D_80083780;
extern s32 D_800893E0;
extern u8 D_800DDE84[];
extern s32 D_800E18A4;
extern s32 D_800E3D7C;

s32 func_800C4490(void *arg0, s32 arg1, s16 arg2) {
    s16 difference;
    s32 amount;
    s32 effect;
    register s32 saved ASM_REG("$16");
    s32 temporary;

    if (arg0 == D_800E3D7C) {
        FIELD(arg0, s32, 0x110) = arg1;
        func_8008D330(arg0, &D_80083780, &D_80082E80, arg0);
        func_800C4624();
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0,
                         (*(u16 *)(D_800DDE84 +
                                   FIELD(arg0, u8, 0x13) * 2) >> 6) & 3,
                         arg1) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C4624();
            return 1;
        }
    }

    amount = (func_800A6D30() & 3) + 7;
    if (amount >= 0x100) {
        amount = 0xFF;
    }

    difference = FIELD(arg0, u8, 0x29) - FIELD(arg0, u8, 0x28);
    if (difference < amount) {
        amount = difference;
    }
    FIELD(arg0, s16, 0x64) = amount;

    if (FIELD(arg0, s32, 0x14) & 0x4000) {
        temporary = func_800990FC();
        {
            register void *call_arg0 ASM_REG("$4");
            register s32 call_arg1 ASM_REG("$5");

            call_arg0 = arg0;
            call_arg1 = temporary;
            saved = call_arg1;
            effect = func_80099734(call_arg0, call_arg1);
        }
        func_80099290(func_80099194(
            &D_800893E0,
            func_8003AD08(FIELD(arg0, s16, 0x64),
                          func_80099194(&D_800E18A4, effect))));
        func_800A5720(saved);
    }

    func_800C4AFC(FIELD(arg0, s32, -0x18), 0x20E020, arg0);
    func_80098B38(arg1);
    D_80083460[5]--;
    return 1;
}

/* MECHANISM: The 0x20 frame and s1/s2 argument holds preserve the exact prologue and CFG.
   Removing func_800A6D30's false argument restores its nop call delay slot.
   Split effect/argument live ranges plus the measured s0 pin yields retail's v0->a1->s0 copy triangle. */
