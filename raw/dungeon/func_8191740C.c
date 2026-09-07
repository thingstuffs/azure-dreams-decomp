#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_80024A34();
extern void func_80024D78() __attribute__((noreturn));
extern void func_80024E60() __attribute__((noreturn));
extern void func_800478B8();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 D_800814A0;

void func_80024C0C(void *arg0, void *arg1, void *arg2) {
    register s32 x ASM_REG("$16");
    register s32 a0 ASM_REG("$4");
    s32 a1;
    s32 a2;
    s32 d0;
    u16 value;
    u8 byte;
    void *object;
    s32 *global;
    s16 state;

    object = FIELD(arg0, void *, 0);
    FIELD(object, u16, 0x14)++;
    state = FIELD(arg0, s16, 4);
    if (state == 0) {
        goto state0;
    }
    if (state == 1) {
        goto state1;
    }
    func_80024E60();

state0:
    FIELD(arg2, u16, 0x1A) += 0x200;
    x = func_800644B8(FIELD(arg0, s16, 0xE));
    x = (x >> 4) * (func_800644B8(FIELD(arg0, s16, 0x10)) >> 4);
    FIELD(arg1, s32, 0) += x * 0x1C;
    x = func_800644B8(FIELD(arg0, s16, 0xE));
    x = (x >> 4) * (func_80064584(FIELD(arg0, s16, 0x10)) >> 4);
    FIELD(arg1, s32, 4) += x * 0x1C;
    FIELD(arg1, s32, 8) += (func_80064584(FIELD(arg0, s16, 0xE)) >> 4) * 0x1C00;
    x = func_800644B8(FIELD(arg0, s16, 0xE));
    x = (x >> 4) * (func_800644B8(FIELD(arg0, s16, 0x10)) >> 4);
    a1 = FIELD(arg1, s32, 0);
    state = FIELD(arg0, s16, 0x12);
    a2 = a1 + x * 0x1C;
    if (state != 0) {
        register s32 cmp ASM_REG("$2");

        a0 = FIELD(arg1, s32, 0xC);
        cmp = a0 < a1;
        ASM_TAILSLOT_PIN(cmp);
        func_80024D78(a0, a1, a2);
        return;
    }
    a0 = FIELD(arg1, s32, 0xC);
    ASM_KEEP(a0);
    if (a1 < a0) {
        register s32 d1 ASM_REG("$3");

        d1 = a1 - a0;
        if (d1 < 0) {
            d1 = -d1;
        }
        ASM_KEEP(d1);
        d0 = a2 - a0;
        if (d0 < 0) {
            d0 = -d0;
        }
        if (d0 < d1) {
            goto done;
        }
        ASM_KEEP(d1);
    }
    ASM_KEEP(a2);
    func_80024A34(arg0, arg1, arg2);
    FIELD(arg0, u16, 4)++;
    func_80024E60();

state1:
    if (FIELD(arg2, u8, 0xC) != 0) {
        byte = FIELD(arg2, u8, 0xE) - 0x20;
        FIELD(arg2, u8, 0xE) = byte;
        FIELD(arg2, u8, 0xD) = byte;
        FIELD(arg2, u8, 0xC) = byte;
    }
    value = FIELD(arg2, u16, 0x1E) + 0x400;
    FIELD(arg2, u16, 0x1E) = value;
    FIELD(arg2, u16, 0x1C) = value;
    func_800478B8(arg2);
    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        object = FIELD(arg0, void *, 0);
        FIELD(object, u16, 0x16)++;
        global = &D_800814A0;
        FIELD(arg0, u16, -2) |= 0x8000;
        *global |= 0x8000;
    }

done:
    return;
}
