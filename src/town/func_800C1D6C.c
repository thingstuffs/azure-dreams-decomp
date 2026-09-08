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

extern s32 func_800352FC(void);
extern s32 func_800C2AB4(S0 *);
extern void func_80053DA8(s32);
extern void func_800BF61C(void) __attribute__((noreturn));
extern void func_800BF634(void) __attribute__((noreturn));
extern void *D_80089900[];

#ifndef NON_MATCHING
register s32 state ASM_REG("$7");   /* MATCH pin: keeps a constant in a register as retail does */
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
        ASM_KEEP(countdown);   /* MATCH pin: load-bearing for the whole function shape */
    }
    value = 0x800000;
    limit = addend + value;
    ASM_KEEP(addend);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if ((u32)state < 6) {
        goto *D_80089900[state];
    }
    return;

L_A: {
        register s32 threshold ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
        register s32 d ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        s32 rhs;

        d = D_80083780.field0;
        rhs = arg1[0];
        d -= rhs;
        threshold = 0x3FFFFF;
        ASM_KEEP(threshold);   /* MATCH pin: retail schedule: same instructions, different order without it */
        if (d < 0) {
            d = -d;
        }
        threshold = threshold < d;
        if (threshold != 0) {
            return;
        }
        if (func_800352FC() == 0) {
            return;
        }
        if (func_800C2AB4(obj) == 0) {
            return;
        }
        func_80053DA8(0x50B);
        value = (u16)obj->f68;
        ASM_KEEP(value);   /* MATCH pin: retail basic-block layout depends on it */
        threshold = 32;
        obj->f6C = threshold;
        func_800BF634();
    }

L_B: {
    s32 below;

    below = D_80083780.field4 < limit;
    if (below != 0) {
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        D_80083780.field4 += 0x40000;
    }
    value = arg2->f1A - 32;
    ASM_TAILSLOT_PIN(value);   /* MATCH pin: retail delay-slot fill depends on it */
    func_800BF61C();
}

L_C:
    if (func_800352FC() != 0) {
        if (func_800C2AB4(obj) != 0) {
            goto L_EXIT;
        }
    }
    obj->f68 = (obj->f68 + 1) % 6;
    return;

L_D:
    value = arg2->f1A + 32;
    arg2->f1A = value;
    if (obj->f6C > 0) {
        goto L_EXIT;
    }
    value = (u16)obj->f68;
    obj->f68 = value + 1;
L_EXIT:
    return;
}
