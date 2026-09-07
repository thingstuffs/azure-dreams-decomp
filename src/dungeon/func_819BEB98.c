#include "common.h"

typedef struct S_80024398_0_pre {
    u16 unk_00;
} S_80024398_0_pre;   /* the 0x2 bytes before arg0 in func_80024398, addressed as arg0[-1] */

typedef struct S_80024398_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4];
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
} S_80024398_0;   /* arg0 in func_80024398 */

typedef struct S_80024398_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80024398_1;   /* parent in func_80024398 */

typedef struct S_80024398_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80024398_2;   /* node in func_80024398 */



extern void func_8002440C(void) __attribute__((noreturn));
extern void func_80024470(void) __attribute__((noreturn));
extern s16 D_8002992E[5];
extern s32 D_800814A0[3];

void func_80024398(void *arg0)
{
    s32 state;
    s16 counter;
    u16 old_value;
    u16 value;
    S_80024398_2 *node;

    state = ((S_80024398_0 *)arg0)->unk_28.s;
    D_8002992E[0] = 1;

    {
        s32 first_test;
        S_80024398_1 *parent;

        parent = ((S_80024398_0 *)arg0)->unk_20;
        first_test = state < 0x1F;
        node = parent->unk_0C;
        if (first_test) {
            goto below_31;
        }
    }

    {
        u32 x;
        u32 y;

        x = node->unk_1C + 0x88;
        y = node->unk_1E + 0x88;
        ASM_KEEP(x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_TAILSLOT_PIN(y);   /* MATCH pin: load-bearing for the whole function shape */
        func_8002440C();
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
        u32 x;
        u32 y;

        x = node->unk_1C + 0x88;
        y = node->unk_1E + 0x88;
        ASM_KEEP(x);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_TAILSLOT_PIN(y);   /* MATCH pin: load-bearing for the whole function shape */
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

        x = node->unk_1C - 0x88;
        y = node->unk_1E - 0x88;
        node->unk_1C = x;
        node->unk_1E = y;
        func_80024470();
        return;
    }

inner:
    old_value = node->unk_1C;
    if (old_value < 0x1000U) {
        value = old_value + 0x88;
        node->unk_1C = value;
        if ((u16)value >= 0x1001U) {
            node->unk_1C = 0x1000U;
        }
    }

    old_value = node->unk_1E;
    if (old_value < 0x1000U) {
        value = old_value + 0x88;
        node->unk_1E = value;
        if ((u16)value >= 0x1001U) {
            node->unk_1E = 0x1000U;
        }
    }

    counter = ((S_80024398_0 *)arg0)->unk_28.u - 1;
    ((S_80024398_0 *)arg0)->unk_28.s = counter;
    if ((counter << 16) <= 0) {
        node->unk_1E = 0x1000U;
        node->unk_1C = 0x1000U;
        ((S_80024398_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    return;
    }
}
