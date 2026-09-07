#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

struct GlobalStruct {
    u16 unk0;
    u16 flags;
    u8 unk4[6];
    u16 counter;
};

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
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
extern void func_80174250(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern struct GlobalStruct D_80083460;
extern void *D_80170858[];
extern u8 D_801713A8[];
extern u8 D_8017449C[];
extern u8 D_801744EC[];
extern u8 D_801744F4[];
extern u8 D_801744FC[];

void func_801738E0(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    register void *arg0 ASM_REG("$17") = in_arg0;
    register void *arg1 ASM_REG("$19") = in_arg1;
    register void *arg2 ASM_REG("$18") = in_arg2;
    register void *arg3 ASM_REG("$16") = in_arg3;
    static void *const sw_keep[] = {
        &&state_zero, &&state_one, &&state_two, &&state_three,
        &&state_four, &&done, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&done, &&done, &&done, &&done,
        &&state_sixteen,
    };
    struct GlobalStruct *global_base;
    register u8 *table ASM_REG("$5");
    u32 clear_mask;
    u32 flags;
    u8 state;

#ifndef __mips__
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
#endif

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 17U) {
        goto done;
    }
    (void)sw_keep;
    goto *D_80170858[state];

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg2, void *, 0x2C) = D_801744FC;
        func_80047784(
            arg2,
            D_801744FC[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        goto state_to_two;
    }
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg3, u32, 0x1C) &= 0xFFFBFFFF;
    if (!(FIELD(arg2, u16, 0x14) & 0x6000)) {
        goto done;
    }
    {
        register s32 val ASM_REG("$2") = 0xFFF80000;
        ASM_KEEP_NV(val);
        table = D_801744F4;
        FIELD(arg1, s32, 0x14) = val;
    }
    goto play_and_advance;

state_one:
    if (FIELD(arg1, s32, 0x14) <= 0xFFFFF) {
        FIELD(arg1, s32, 0x14) += 0x20000;
    }
    if (FIELD(arg0, s32, 0x90) < 0) {
        goto done;
    }
    FIELD(arg0, s32, 0x90) = 0;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg2, void *, 0x2C) = D_801744FC;
    func_80047784(
        arg2,
        D_801744FC[
            ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A9A0C(arg3);

state_to_two:
    {
        register struct GlobalStruct *g ASM_REG("$3") = &D_80083460;
        g->counter--;
    }
    FIELD(arg0, u8, 0x9B) = 2;
    goto done;

state_two:
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x08000000;
    if ((func_80042900(arg3, 1) << 16) == 0) {
        FIELD(arg2, void *, 0x2C) = D_801744F4;
        func_80047784(
            arg2,
            D_801744F4[
                ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        flags = FIELD(arg3, u32, 0x1C) | 0x40000;
        FIELD(arg3, u32, 0x1C) = flags;
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            clear_mask = ~0x200U;
            goto clear_200;
        }
        {
            register struct GlobalStruct *g ASM_REG("$2") = &D_80083460;
            register u16 c = g->counter + 1;
            ASM_KEEP_NV(c);
            g->counter = c;
        }
        goto advance_state;
    }

    global_base = &D_80083460;
    if (global_base->flags & 0x1000) {
        goto done;
    }
    if (FIELD(arg3, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if (FIELD(arg3, u8, 0x25) == 0) {
        if (global_base->flags & 0x2008) {
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
        func_800AA888(arg0, arg1, arg2, arg3);
        FIELD(arg0, s16, 0xA8) = 0;
        func_80174250(arg0, arg1, arg2, arg3);
        goto done;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(
                 arg3, (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20)
             << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 coordinate = FIELD(arg2, s8, 0x26);

        if ((((coordinate == FIELD(origin, s8, 0x26)) && (coordinate >= 0)) ||
             (func_8009FD40(origin, arg2) < 2)) &&
            ((func_800A6D30() & 7) == 0)) {
            func_80042B68(arg3, 1);
        }
    }
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }

    FIELD(arg2, void *, 0x2C) = D_801744F4;
    func_80047784(
        arg2,
        D_801744F4[
            ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    flags = FIELD(arg3, u32, 0x1C) | 0x40000;
    FIELD(arg3, u32, 0x1C) = flags;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        clear_mask = ~0x200U;
        goto clear_200;
    }
    {
        register struct GlobalStruct *g ASM_REG("$2") = &D_80083460;
        g->counter++;
    }
    goto advance_state;

state_three:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    table = D_801744EC;

play_and_advance:
    FIELD(arg2, void *, 0x2C) = table;
    func_80047784(
        arg2,
        *(u8 *)((((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7) + (u32)table),
        0);

advance_state:
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_four:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0xFFF80000;
    FIELD(arg0, s16, 0xA8) = 8;
    FIELD(arg0, u16, 0x98) &= 0xBFFF;
    FIELD(arg2, void *, 0x2C) = D_8017449C;
    func_80047784(
        arg2,
        D_8017449C[
            ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, u8, 0x9B) = 0x10;
    goto done;

state_sixteen:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg0, u16, 0x98) &= 0xFFF7;
    FIELD(arg3, u32, 0x1C) |= 0x08000000;
    FIELD(arg0, u16, 0x98) |= 0x4000;
    FIELD(arg1, s32, 0x14) = 0;
    {
        register struct GlobalStruct *g ASM_REG("$3") = &D_80083460;
        g->counter--;
    }
    FIELD(arg3, u32, 0x1C) &= ~0x200;
    FIELD(arg0, void *, 0x8C) = D_801713A8;
    goto done;

clear_200:
    FIELD(arg3, u32, 0x1C) = clear_mask & flags;
    FIELD(arg0, void *, 0x8C) = D_801713A8;

done:
    return;
}
