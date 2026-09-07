#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 rand(void);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80173D10(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801711A4[];
extern u8 D_80174184[];
extern u8 D_801741CC[];

void func_8017352C(void *in_arg0, void *in_arg1, void *in_arg2, void *in_arg3)
{
    register void *arg0 ASM_REG("$16");
    register void *arg1 ASM_REG("$20");
    register void *arg2 ASM_REG("$19");
    register void *arg3 ASM_REG("$17");
    register u8 *part20 ASM_REG("$18");
    register u8 *part28 ASM_REG("$22");
    u8 *global_base;
    register u8 *body ASM_REG("$2");
    register u8 *counter_base ASM_REG("$3");
    s32 flags;
    s32 state;
    u16 timer;
    u16 count;

    arg0 = in_arg0;
    arg1 = in_arg1;
    arg2 = in_arg2;
#ifndef __mips__
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
#endif
    body = FIELD(arg0, u8 *, 0xA4);
    state = FIELD(arg0, u8, 0x9B);
    part20 = body + 0x20;
    part28 = body + 0x28;
#ifndef __mips__
    ASM_KEEP(part20);
    ASM_KEEP(part28);
#endif
    arg3 = in_arg3;
#ifndef __mips__
    ASM_KEEP(arg3);
#endif
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
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
    FIELD(arg0, s32, 0x90) += 0x80000;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg2, void *, 0x2C) = D_801741CC;
    func_80047784(arg2,
        D_801741CC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    counter_base = (u8 *)&D_80083460;
    FIELD(arg0, u16, 0x96) = 0;
    count = FIELD(counter_base, u16, 0xA) - 1;
    goto store_count;

state_one:
    if ((func_80042900(arg3, 1) << 16) == 0) {
        goto animate;
    }
    global_base = (u8 *)&D_80083460;
    if (FIELD(global_base, u16, 2) & 0x1000) {
        goto done;
    }
    if (FIELD(arg3, s16, 0x64) != 0) {
        if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
            goto done;
        }
    }
    if (FIELD(arg3, u8, 0x25) == 0) {
        if (FIELD(global_base, u16, 2) & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, arg1, arg2, arg3);
        goto done;
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
        FIELD(arg0, u16, 0xA8) = 0;
        func_80173D10(arg0, arg1, arg2, arg3);
        goto done;
    }

    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) <= 0) {
        FIELD(part20, u16, 4) &= 0x7FFF;
        func_80047784(part28, 0x27, 0);
        FIELD(arg0, u16, 0x96) = (rand() & 0xF) + 0x20;
    }
    if (FIELD(part28, u16, 0x14) & 0x6000) {
        FIELD(part20, u16, 4) |= 0x8000;
    }
    if (FIELD(arg3, s8, 0x6D) == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        void *owner = D_800814A8;

        if ((func_8009A180(arg3,
                (u8 *)FIELD(owner, void *, 0x58) + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        u8 *origin = D_80082E80;
        s8 tile = FIELD(arg2, s8, 0x26);

        if (((tile == FIELD(origin, s8, 0x26)) && (tile >= 0)) ||
            ((s16)func_8009FD40(origin, arg2) < 2)) {
            if (!(func_800A6D30() & 7)) {
                func_80042B68(arg3, 1);
            }
        }
    }
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }

animate:
    FIELD(arg2, void *, 0x2C) = D_80174184;
    func_80047784(arg2,
        D_80174184[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg3, u32, 0x1C) |= 0x40000;
    FIELD(part20, u16, 4) |= 0x8000;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto clear_flag;
    }
    counter_base = (u8 *)3;
    FIELD(arg0, u16, 0x96) = (s32)counter_base;
    FIELD(arg0, u16, 0x98) &= 0xBFFF;
    counter_base = (u8 *)&D_80083460;
    count = FIELD(counter_base, u16, 0xA) + 1;

store_count:
    FIELD(counter_base, u16, 0xA) = count;
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) <= 0) {
        FIELD(arg0, u16, 0x98) |= 0x4000;
        FIELD(arg1, s32, 0x14) = 0xFFF80000;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    counter_base = (u8 *)&D_80083460;
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, u16, 0xA8) = 0;
    FIELD(counter_base, u16, 0xA)--;

clear_flag:
    FIELD(arg3, u32, 0x1C) &= -0x201;
    FIELD(arg0, void *, 0x8C) = D_801711A4;

done:
    return;
}
