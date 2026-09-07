#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8002440C(void) __attribute__((noreturn));
extern void func_80024470(void) __attribute__((noreturn));
extern s16 D_8002992E[5];
extern s32 D_800814A0[3];

void func_80024398(void *arg0)
{
    register s32 state ASM_REG("$6");
    s16 counter;
    u16 old_value;
    u16 value;
    register void *node ASM_REG("$5");

    state = FIELD(arg0, s16, 0x28);
    D_8002992E[0] = 1;

    {
        s32 first_test;
        void *parent;

        parent = FIELD(arg0, void *, 0x20);
        first_test = state < 0x1F;
        ASM_USE(first_test);
        node = FIELD(parent, void *, 0xC);
        if (first_test) {
            goto below_31;
        }
    }

    {
        register u32 x ASM_REG("$2");
        register u32 y ASM_REG("$3");

        x = FIELD(node, u16, 0x1C) + 0x88;
        y = FIELD(node, u16, 0x1E) + 0x88;
        ASM_KEEP(node);
        ASM_KEEP(state);
        ASM_KEEP(x);
        ASM_KEEP(y);
        ASM_TAILSLOT_PIN(y);
        func_8002440C();
        ASM_MEM_BARRIER();
        return;
    }

below_31:
    {
        s32 test;

    test = state < 0x19;
    if (!test) {
        goto decrement;
    }
    test = state < 0x10;
    if (!test) {
        register u32 x ASM_REG("$2");
        register u32 y ASM_REG("$3");

        x = FIELD(node, u16, 0x1C) + 0x88;
        y = FIELD(node, u16, 0x1E) + 0x88;
        ASM_KEEP(node);
        ASM_KEEP(state);
        ASM_KEEP(x);
        ASM_KEEP(y);
        ASM_TAILSLOT_PIN(y);
        func_8002440C();
        return;
    }
    test = state < 0xA;
    if (test) {
        goto inner;
    }

decrement:
    {
        u32 x;
        u32 y;

        x = FIELD(node, u16, 0x1C) - 0x88;
        y = FIELD(node, u16, 0x1E) - 0x88;
        FIELD(node, u16, 0x1C) = x;
        FIELD(node, u16, 0x1E) = y;
        func_80024470();
        return;
    }

inner:
    old_value = FIELD(node, u16, 0x1C);
    if (old_value < 0x1000U) {
        value = old_value + 0x88;
        FIELD(node, u16, 0x1C) = value;
        if ((u16)value >= 0x1001U) {
            FIELD(node, u16, 0x1C) = 0x1000U;
        }
    }

    old_value = FIELD(node, u16, 0x1E);
    if (old_value < 0x1000U) {
        value = old_value + 0x88;
        FIELD(node, u16, 0x1E) = value;
        if ((u16)value >= 0x1001U) {
            FIELD(node, u16, 0x1E) = 0x1000U;
        }
    }

    counter = FIELD(arg0, u16, 0x28) - 1;
    FIELD(arg0, s16, 0x28) = counter;
    if ((counter << 16) <= 0) {
        FIELD(node, u16, 0x1E) = 0x1000U;
        FIELD(node, u16, 0x1C) = 0x1000U;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    return;
    }
}
