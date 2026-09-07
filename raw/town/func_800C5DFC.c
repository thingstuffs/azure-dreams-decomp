#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern s32 func_800C30E0(void *arg0, void *arg1, void *arg2);
extern s16 func_800C2B38(void *arg0, s32 arg1, s32 arg2);
extern void func_800C3688(void) __attribute__((noreturn));
extern void func_800C36B0(void);
extern void func_800C36B0_zero(void) __asm__("func_800C36B0");
extern void func_800C3764(void) __attribute__((noreturn));
extern void func_800C37C4(void *arg0, void *arg1, void *arg2);
extern int abs(int);

extern s32 D_800D4FE8[4];
extern s32 D_800D4FF8[4];
extern s32 D_800D5008[4];
extern s32 D_800D5018[4];

void func_800C355C(void *arg0, void *arg1, void *arg2)
{
    s32 pos_x;
    register s32 step_x ASM_REG("$5");
    register s32 pos_y ASM_REG("$3");
    s32 step_y;
    s32 angle;
    s32 quadrant;
    s32 value;
    s32 limit;
    s32 *p;

    if (func_800C30E0(arg0, arg1, arg2) != 0) {
        return;
    }

    p = (s32 *)arg1;
    pos_x = p[0];
    step_x = p[3];
    pos_x += step_x;
    pos_y = *(volatile s32 *)((u8 *)arg1 + 4);
    step_y = p[4];
    pos_y += step_y;
    FIELD(arg1, s32, 0) = pos_x;
    FIELD(arg1, s32, 4) = pos_y;
    FIELD(arg1, s16, 0xa) = func_800C2B38(arg1, step_x, step_y);

    angle = 0x400 - FIELD(arg0, s16, 0x72);
    quadrant = (angle / 0x400) & 3;

    if (quadrant == 1) {
        goto case_one;
    }
    if (quadrant < 2) {
        if (quadrant == 0) {
            goto case_zero;
        }
        func_800C3688();
        return;
    }
    if (quadrant == 2) {
        goto case_two;
    }
    goto case_three;

case_zero:
    if (FIELD(arg0, s16, 0x84) + FIELD(arg0, s16, 0x8c) < FIELD(arg1, s16, 2)) {
        register u16 bound_x ASM_REG("$4");
        register u16 bound_y ASM_REG("$3");
        register u16 bound_sum ASM_REG("$2");
        bound_x = FIELD(arg0, u16, 0x84);
        bound_y = FIELD(arg0, u16, 0x8c);
        bound_sum = bound_y + bound_x;
        FIELD(arg1, u16, 2) = bound_sum;
        goto case_zero_call;
    }
    goto apply;

case_zero_call:
    func_800C36B0_zero();
    return;

case_one:
    if (FIELD(arg0, s16, 0x86) + FIELD(arg0, s16, 0x8e) < FIELD(arg1, s16, 6)) {
        FIELD(arg1, u16, 6) = FIELD(arg0, u16, 0x86) + FIELD(arg0, u16, 0x8e);
        func_800C36B0();
        return;
    }
    goto apply;

case_two:
    if (FIELD(arg1, s16, 2) < FIELD(arg0, s16, 0x84) - FIELD(arg0, s16, 0x8c)) {
        u16 bound_x;
        u16 bound_y;
        bound_x = FIELD(arg0, u16, 0x84);
        bound_y = FIELD(arg0, u16, 0x8c);
        FIELD(arg1, u16, 2) = bound_x - bound_y;
        do {
            func_800C36B0();
        } while (0);
        return;
    }
    goto apply;

case_three:
    if (FIELD(arg1, s16, 6) < FIELD(arg0, s16, 0x86) - FIELD(arg0, s16, 0x8e)) {
        u16 bound_x;
        u16 bound_y;
        bound_x = FIELD(arg0, u16, 0x86);
        bound_y = FIELD(arg0, u16, 0x8e);
        FIELD(arg1, u16, 6) = bound_x - bound_y;
        func_800C37C4(arg0, arg1, arg2);
        func_800C3764();
        return;
    }

apply:
    limit = 0x20000;

    value = FIELD(arg1, s32, 0xc) + D_800D4FE8[quadrant];
    FIELD(arg1, s32, 0xc) = value;
    value = abs(value);
    value = limit < value;
    if (value != 0) {
        FIELD(arg1, s32, 0xc) = D_800D4FF8[quadrant];
    }

    value = FIELD(arg1, s32, 0x10) + D_800D5008[quadrant];
    FIELD(arg1, s32, 0x10) = value;
    value = abs(value);
    value = limit < value;
    if (value != 0) {
        FIELD(arg1, s32, 0x10) = D_800D5018[quadrant];
    }
}
