#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801744F8(void) __attribute__((noreturn));
extern void func_80174550(void) __attribute__((noreturn));
extern void func_80174574(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801710EC;
extern u8 D_80175EA0[];
extern u8 D_80175EC0[];

void func_80174214(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    func_80174550();

at_least_two:
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_two;
    }
    func_80174550();

state_zero:
    {
        s32 *base;
        u8 *table;

        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto done;
        }

        base = &D_80083460;
        FIELD(base, u16, 0xA)--;
        table = D_80175EA0;
        if (FIELD(arg2, void *, 0x2C) != table) {
            FIELD(arg2, void *, 0x2C) = table;
            func_80047784(arg2,
                table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            func_801744F8();
        }
        goto increment_state;
    }

state_one:
    {
        u8 *global;
        u32 flags;

        if (FIELD(arg3, u8, 0x25) != 0) {
            s32 *base;

            FIELD(arg2, void *, 0x2C) = D_80175EC0;
            func_80047784(arg2,
                D_80175EC0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg3, u32, 0x1C) |= 0x40000;
            base = &D_80083460;
            FIELD(base, u16, 0xA)++;
            func_801744F8();
        }

        ASM_SCHED_BARRIER();
        global = (u8 *)&D_80083460;
        if (FIELD(global, u16, 2) & 0x1000) {
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

        flags = FIELD(arg3, u32, 0x1C);
        {
        register void *call_arg0 ASM_REG("$4") = arg0;

        if (flags & 0x100) {
            func_800AA258(call_arg0, arg1, arg2, arg3);
            func_80174550();
        }

        ASM_KEEP(call_arg0);
        if (flags & 0x80000) {
            u16 old_value;
            u16 amount;

            func_800AA888(call_arg0, arg1, arg2, arg3);
            old_value = FIELD(arg0, u16, 0x92);
            amount = FIELD(arg0, u16, 0xA2);
            FIELD(arg0, u16, 0xA2) = 0;
            FIELD(arg0, u16, 0x9E) = 0;
            FIELD(arg0, u16, 0x92) = old_value - amount;
            func_80174574(arg0, arg1, arg2, arg3);
            func_80174550();
        }
        }

        if (FIELD(arg3, s8, 0x6D) == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(arg3,
                    (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) << 16) != 0) {
                goto done;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (FIELD(arg3, u8, 0x25) == 0) {
            goto done;
        }

        FIELD(arg2, void *, 0x2C) = D_80175EC0;
        func_80047784(arg2,
            D_80175EC0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(global, u16, 0xA)++;
    }

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    func_80174550();

state_two:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        s32 *base;

        base = &D_80083460;
        FIELD(base, u16, 0xA)--;
        FIELD(arg3, u32, 0x1C) &= ~8;
        FIELD(arg0, void *, 0x8C) = &D_801710EC;
    }

done:
    return;
}

/* MECHANISM: Four live argument bases plus the held D_80083460 base produce the retail 0x28 frame.
   The callback-equality edge, state continuations, and exact callee ABIs restore the 216-word CFG.
   Scheduler barriers and a guarded $a0 carrier close the three remaining delay-slot rotations. */
