#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80024808() __attribute__((noreturn));
extern void func_80024860(void) __attribute__((noreturn));

void func_81844F2C(void *arg0) {
    register u8 *base ASM_REG("$5");
    register u8 *page ASM_REG("$3");
    register s32 call_a0;
    register u32 call_a2 ASM_REG("$6");
    register u32 sum ASM_REG("$2");
    register u32 addend ASM_REG("$3");
    register s32 state ASM_REG("$3");
    register u32 delta ASM_REG("$6");
    register u32 next_state ASM_REG("$2");
    void *entity;
    u8 *cursor;

    base = arg0;
    ASM_KEEP(base);
    entity = M2C_FIELD(base, void **, 0);
    M2C_FIELD(entity, u16 *, 0x52) =
        (u16)(M2C_FIELD(entity, u16 *, 0x52) | 0x8000);

    sum = M2C_FIELD(base, u16 *, 4);
    addend = M2C_FIELD(base, u16 *, 0xC);
    call_a0 = M2C_FIELD(base, u16 *, 0x2A);
    sum += addend;
    M2C_FIELD(base, u16 *, 4) = (u16)sum;
    ASM_KEEP(base);
    sum = M2C_FIELD(base, u16 *, 6);
    addend = M2C_FIELD(base, u16 *, 0xE);
    call_a2 = M2C_FIELD(base, volatile u16 *, 0x2C);
    sum += addend;
    ASM_KEEP_NV(base);
    state = M2C_FIELD(base, s16 *, 0x2C);
    ASM_KEEP(call_a0);
    call_a0 -= 1;
    M2C_FIELD(base, volatile u16 *, 0x2A) = (u16)call_a0;
    M2C_FIELD(base, volatile u16 *, 6) = (u16)sum;

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_at_least_2;
    }
    if (state == 0) {
        goto state_0;
    }
    ASM_KEEP_NV(call_a0);
    ASM_KEEP_NV(base);
    ASM_KEEP_NV(call_a2);
    func_80024860();
    return;

state_at_least_2:
    if (state == 2) {
        goto state_2;
    }
    ASM_KEEP_NV(call_a0);
    ASM_KEEP_NV(base);
    ASM_KEEP_NV(call_a2);
    func_80024860();
    return;

state_0:
    call_a0 = 7 - (s16)call_a0;
    if (call_a0 < 5) {
        M2C_FIELD(base + (call_a0 * 4), u32 *, 0x14) = 0x00808080;
        func_80024808(call_a0, base, call_a2);
        return;
    }

    call_a0 = 4;
    delta = 0xFFDFDFE0;
    cursor = base + 0x10;
    do {
        call_a0 -= 1;
        M2C_FIELD(cursor, volatile u32 *, 0x14) += delta;
        cursor -= 4;
    } while (call_a0 >= 0);

    if (M2C_FIELD(base, s16 *, 0x2A) > 0) {
        return;
    }
    M2C_FIELD(base, u16 *, 0x2A) = 3;
    M2C_FIELD(base, u16 *, 0x2C) += 1;
    ASM_KEEP_NV(call_a0);
    ASM_KEEP_NV(base);
    ASM_KEEP_NV(call_a2);
    func_80024860();
    return;

state_1:
    if ((call_a0 << 16) > 0) {
        return;
    }
    next_state = call_a2 + 1;
    M2C_FIELD(base, u16 *, 0x2C) = (u16)next_state;
    ASM_KEEP_NV(call_a0);
    ASM_KEEP_NV(base);
    ASM_KEEP_NV(call_a2);
    func_80024860();
    return;

state_2:
    page = (u8 *)0x80080000;
    ASM_KEEP(page);
    M2C_FIELD(base, u16 *, -2) =
        (u16)(M2C_FIELD(base, u16 *, -2) | 0x8000);
    M2C_FIELD(page, volatile u32 *, 0x14A0) |= 0x8000;
}
