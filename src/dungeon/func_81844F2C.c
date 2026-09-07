#include "common.h"

typedef struct S_81844F2C_0_pre {
    u16 unk_00;
} S_81844F2C_0_pre;   /* the 0x2 bytes before base in func_81844F2C, addressed as base[-1] */

typedef struct S_81844F2C_0 {
    void * unk_00;
    u16 unk_04;
    union { u16 s; volatile u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x1A];
    union { u16 s; volatile u16 u; s16 p; } unk_2A;   /* accessed as both */
    union { volatile u16 s; s16 u; u16 p; } unk_2C;   /* accessed as both */
} S_81844F2C_0;   /* base in func_81844F2C */

typedef struct S_81844F2C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_81844F2C_1;   /* entity in func_81844F2C */

typedef struct S_81844F2C_2 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_81844F2C_2;   /* base + (call_a0 * 4) in func_81844F2C */

typedef struct S_81844F2C_3 {
    u8 pad_00[0x14];
    volatile u32 unk_14;
} S_81844F2C_3;   /* cursor in func_81844F2C */

typedef struct S_81844F2C_4 {
    u8 pad_00[0x14A0];
    volatile u32 unk_14A0;
} S_81844F2C_4;   /* page in func_81844F2C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80024808() __attribute__((noreturn));
extern void func_80024860(void) __attribute__((noreturn));

void func_81844F2C(void *arg0) {
    u8 *base;
    register u8 *page ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */
    register s32 call_a0;
    register u32 call_a2 ASM_REG("$6");   /* MATCH pin: retail immediate-load split depends on it */
    u32 sum;
    u32 addend;
    s32 state;
    u32 delta;
    register u32 next_state ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    S_81844F2C_1 *entity;
    u8 *cursor;

    base = arg0;
    entity = ((S_81844F2C_0 *)base)->unk_00;
    entity->unk_52 =
        (u16)(entity->unk_52 | 0x8000);

    sum = ((S_81844F2C_0 *)base)->unk_04;
    addend = ((S_81844F2C_0 *)base)->unk_0C;
    call_a0 = ((S_81844F2C_0 *)base)->unk_2A.s;
    sum += addend;
    ((S_81844F2C_0 *)base)->unk_04 = (u16)sum;
    ASM_KEEP(base);   /* MATCH pin: retail schedule: same instructions, different order without it */
    sum = ((S_81844F2C_0 *)base)->unk_06.s;
    addend = ((S_81844F2C_0 *)base)->unk_0E;
    call_a2 = ((S_81844F2C_0 *)base)->unk_2C.s;
    sum += addend;
    state = ((S_81844F2C_0 *)base)->unk_2C.u;
    ASM_KEEP(call_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_a0 -= 1;
    ((S_81844F2C_0 *)base)->unk_2A.u = (u16)call_a0;
    ((S_81844F2C_0 *)base)->unk_06.u = (u16)sum;

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_at_least_2;
    }
    if (state == 0) {
        goto state_0;
    }
    func_80024860();
    return;

state_at_least_2:
    if (state == 2) {
        goto state_2;
    }
    func_80024860();
    return;

state_0:
    call_a0 = 7 - (s16)call_a0;
    if (call_a0 < 5) {
        ((S_81844F2C_2 *)(base + (call_a0 * 4)))->unk_14 = 0x00808080;
        func_80024808(call_a0, base, call_a2);
        return;
    }

    call_a0 = 4;
    delta = 0xFFDFDFE0;
    cursor = base + 0x10;
    do {
        call_a0 -= 1;
        ((S_81844F2C_3 *)cursor)->unk_14 += delta;
        cursor -= 4;
    } while (call_a0 >= 0);

    if (((S_81844F2C_0 *)base)->unk_2A.p > 0) {
        return;
    }
    ((S_81844F2C_0 *)base)->unk_2A.s = 3;
    ((S_81844F2C_0 *)base)->unk_2C.p += 1;
    func_80024860();
    return;

state_1:
    if ((call_a0 << 16) > 0) {
        return;
    }
    next_state = call_a2 + 1;
    ((S_81844F2C_0 *)base)->unk_2C.p = (u16)next_state;
    func_80024860();
    return;

state_2:
    page = (u8 *)0x80080000;
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_81844F2C_0_pre *)base)[-1].unk_00 =
        (u16)(((S_81844F2C_0_pre *)base)[-1].unk_00 | 0x8000);
    ((S_81844F2C_4 *)page)->unk_14A0 |= 0x8000;
}
