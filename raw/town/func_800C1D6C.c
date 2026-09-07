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
extern void func_800BF640(void) __attribute__((noreturn));
extern void *D_80089900[];

#ifndef NON_MATCHING
register s32 state ASM_REG("$7");
#else
static s32 state;
#endif

void func_800BF4CC(S0 *self, s32 *arg1, S1 *arg2) {
    register S0 *obj ASM_REG("$16") = self;
    register s32 limit ASM_REG("$8");
    register s32 value ASM_REG("$2");
    register s32 addend ASM_REG("$3");
    static void *const keepalive[4] = {&&L_A, &&L_B, &&L_C, &&L_D};

    {
        register s32 countdown ASM_REG("$2");

        countdown = (u16)obj->f6C;
        addend = arg1[1];
        state = obj->f68;
        countdown--;
        obj->f6C = countdown;
        ASM_KEEP(countdown);
    }
    value = 0x800000;
    limit = addend + value;
    ASM_KEEP(addend);
    if ((u32)state < 6) {
        goto *D_80089900[state];
    }
    return;

L_A: {
        register s32 threshold ASM_REG("$3");
        register s32 d ASM_REG("$2");
        s32 rhs;

        d = D_80083780.field0;
        rhs = arg1[0];
        d -= rhs;
        threshold = 0x3FFFFF;
        ASM_KEEP(threshold);
        if (d < 0) {
            d = -d;
        }
        ASM_KEEP(d);
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
        ASM_KEEP(value);
        threshold = 32;
        ASM_KEEP(value);
        ASM_KEEP(threshold);
        obj->f6C = threshold;
        func_800BF634();
    }

L_B: {
    register s32 below ASM_REG("$2");

    below = D_80083780.field4 < limit;
    ASM_KEEP(below);
    if (below != 0) {
        ASM_SCHED_BARRIER();
        D_80083780.field4 += 0x40000;
    }
    value = arg2->f1A - 32;
    ASM_TAILSLOT_PIN(value);
    func_800BF61C();
}

L_C:
    if (func_800352FC() != 0) {
        if (func_800C2AB4(obj) != 0) {
            goto L_EXIT;
        }
    }
    obj->f68 = (obj->f68 + 1) % 6;
    func_800BF640();

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
