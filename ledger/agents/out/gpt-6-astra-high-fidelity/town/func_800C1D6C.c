#include "common.h"

typedef struct S0 {
    char pad0[0x68];
    s16 f68;
    char pad6A[2];
    s16 f6C;
} S0;

typedef struct S1 {
    char pad0[0x1A];
    u16 f1A;
} S1;

typedef struct S80083780 {
    s32 field0;
    s32 field4;
    s32 field8;
} S80083780;

extern S80083780 D_80083780;

extern s32 func_800352FC(s32, s32 *, S1 *);
extern s32 func_800C2AB4(S0 *);
extern void SD_Call(s32);
extern void *D_80089900[];

#ifndef NON_MATCHING
register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#else
static s32 state;
#endif

void func_800BF4CC(S0 *self, s32 *arg1, S1 *arg2) {
    S0 *obj = self;
    s32 limit;
    s32 value;
    s32 addend;
    static void *const keepalive[4] = {&&L_A, &&L_B, &&L_C, &&L_D};

    {
        s32 countdown;

        countdown = (u16)obj->f6C;
        addend = arg1[1];
        state = obj->f68;
        countdown--;
        obj->f6C = countdown;
        ASM_KEEP(countdown);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    }
    value = 0x800000;
    limit = addend + value;
    ASM_KEEP(addend);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if ((u32)state < 6) {
        goto *D_80089900[state];
    }
    return;

L_A: {
        register s32 threshold ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 d ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 rhs;

        d = D_80083780.field0;
        rhs = arg1[0];
        d -= rhs;
        threshold = 0x3FFFFF;
        ASM_KEEP(threshold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (d < 0) {
            d = -d;
        }
        threshold = threshold < d;
        if (threshold != 0) {
            return;
        }
        if (func_800352FC(rhs, arg1, arg2) == 0) {
            return;
        }
        if (func_800C2AB4(obj) == 0) {
            return;
        }
        SD_Call(0x50B);
        value = (u16)obj->f68;
        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        threshold = 32;
        obj->f6C = threshold;
        goto L_INCREMENT;
    }

L_B: {
    s32 below;

    below = D_80083780.field4 < limit;
    if (below != 0) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        D_80083780.field4 += 0x40000;
    }
    value = arg2->f1A - 32;
    goto L_STORE;
}

L_C:
    if (func_800352FC((s32)self, arg1, arg2) != 0) {
        if (func_800C2AB4(obj) != 0) {
            goto L_EXIT;
        }
    }
    obj->f68 = (obj->f68 + 1) % 6;
    return;

L_D:
    value = arg2->f1A + 32;
L_STORE:
    arg2->f1A = value;
    if (obj->f6C > 0) {
        goto L_EXIT;
    }
    value = (u16)obj->f68;
L_INCREMENT:
    obj->f68 = value + 1;
L_EXIT:
    return;
}
