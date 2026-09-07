#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_801719DC;
extern u8 D_80174684[];
extern u8 D_8017468C[];

void func_80173CD4(void *in0, void *in1, void *in2, void *in3)
{
    s32 state;
    register void *arg0 ASM_REG("$18") = in0;
    register void *arg1 ASM_REG("$19") = in1;
    register void *arg2 ASM_REG("$17") = in2;
    register void *arg3 ASM_REG("$16");
    register u8 *global ASM_REG("$20");

    state = FIELD(arg0, u8, 0x9B);
    arg3 = in3;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto at_least_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

at_least_two:
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    {
        u8 *base;
        u8 *table;
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto done;
        }
        table = D_80174684;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        base = (u8 *)&D_80083460;
        FIELD(base, u16, 0xA)--;
        goto increment_state;
    }

state_one:
    {
        register u32 global_page ASM_REG("$2");
        u32 flags;

        if ((func_80042900(arg3, 1) << 16) == 0) {
            goto animate;
        }

        global_page = 0x80080000;
        ASM_KEEP(global_page);
        global = (u8 *)(global_page + 0x3460);
        ASM_KEEP(global);
        if (FIELD(global, u16, 2) & 0x1000) {
            goto done;
        }

        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }

        if (FIELD(arg3, u8, 0x25) == 0) {
            if (FIELD(global, u16, 2) & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }

        flags = FIELD(arg3, u32, 0x1C);
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }

        if (flags & 0x80000) {
            u16 old_value;
            u16 amount;
            u32 saved;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = FIELD(arg0, u16, 0x92);
            amount = FIELD(arg0, u16, 0xA6);
            saved = FIELD(arg0, u32, 0xA4);
            FIELD(arg0, u16, 0xA6) = 0;
            FIELD(arg0, u16, 0xB8) = 0;
            FIELD(arg0, u32, 0xAC) = 0;
            FIELD(arg0, u32, 0xB0) = 0;
            FIELD(arg0, u16, 0x92) = old_value - amount;
            FIELD(arg0, u32, 0xA8) = saved;
            func_801743F0(arg0, arg1, arg2, arg3);
            goto done;
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
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin;
            s8 coordinate;

            origin = D_80082E80;
            coordinate = FIELD(arg2, s8, 0x26);
            if ((((coordinate == FIELD(origin, s8, 0x26)) &&
                    (coordinate >= 0)) ||
                    (func_8009FD40(origin, arg2) < 2)) &&
                    !(func_800A6D30() & 7)) {
                func_80042B68(arg3, 1);
            }
        }

        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto done;
        }
    }

animate:
    {
        u8 *table;

        table = D_8017468C;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg3, u32, 0x1C) |= 0x40000;
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            goto set_pointer;
        }

        {
            register u8 *base ASM_REG("$2") = (u8 *)&D_80083460;
            ASM_KEEP(base);
            FIELD(base, u16, 0xA)++;
        }
    }

increment_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        register u8 *base ASM_REG("$2");

        base = (u8 *)&D_80083460;
        ASM_KEEP(base);
        FIELD(base, u16, 0xA)--;
        goto set_pointer;
    }
    goto done;

set_pointer:
    FIELD(arg0, void *, 0x8C) = &D_801719DC;

done:
    return;
}

/* MECHANISM: Delayed a3->s0 plus removal of the four leading ASM_KEEP fences
   restores the 0x28 prologue/save order and fills the first branch delay.
   A named state-zero base, v0-pinned tail bases, split page, and zero-arg
   func_800A6D30 prevent RMW commoning and collapse the +1-word cascade. */
