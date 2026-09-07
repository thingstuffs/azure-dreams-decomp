#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;
extern s32 D_80083780;

extern void func_80033D08(void *);
extern s32 func_8009CFE0(void);

void func_800B9998(void *arg0, void *arg1, void *arg2) {
    register u8 *p1 ASM_REG("$17") = arg1;
    register u8 *p2 ASM_REG("$18") = arg2;
    s8 *byte_ptr;
    u8 *town;
    s32 dx;
    s32 dy;
    s32 dx_ok;
    s32 sum;
    register s32 arg1_x ASM_REG("$3");
    register s32 arg1_y ASM_REG("$4");
    s32 angle;
    s32 raw_angle;
    s32 addend;

    if (func_8009CFE0() != 0) {
        byte_ptr = FIELD(arg0, s8 *, 0x98);
        if (byte_ptr != 0) {
            *byte_ptr = 0;
        }
        func_80033D08(arg0);
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto epilogue;
    }

    raw_angle = FIELD(arg0, u16, 0x66);
    angle = FIELD(arg0, s16, 0x66);
    if (angle >= 0x100) {
        FIELD(arg0, u16, 0x66) = raw_angle - 0x20;
        goto angle_ready;
    }
    if (angle >= 0x10) {
        FIELD(arg0, u16, 0x66) = raw_angle - 0x10;
        goto angle_ready;
    }
    FIELD(arg0, u16, 0x66) = 0;

    angle_ready:
    town = (u8 *)&D_80083780;
    dx = FIELD(town, s16, 2);
    arg1_x = FIELD(p1, s16, 2);
    arg1_y = FIELD(p1, s16, 6);
    dx -= arg1_x;
    ASM_KEEP(arg1_x);
    ASM_KEEP(p1);
    if (dx < 0) {
        dx = -dx;
    }
    dx = (s16)dx;
    ASM_USE(dx);
    dy = FIELD(town, s16, 6);
    dx_ok = dx < 0x81;
    ASM_USE(dx_ok);
    dy -= arg1_y;
    ASM_KEEP(arg1_y);
    if (dy < 0) {
        dy = -dy;
    }

    if (dx_ok && ((s16)dy < 0x81)) {
        sum = (FIELD(town, s16, 0xE) * FIELD(town, s16, 0xE)) +
              (FIELD(town, s16, 0x12) * FIELD(town, s16, 0x12));
        FIELD(arg0, u16, 0x66) =
            FIELD(arg0, u16, 0x66) +
            ((s32)(sum + ((u32)sum >> 31)) >> 1);
    }

    if (FIELD(arg0, s16, 0x66) >= 0x601) {
        FIELD(arg0, u16, 0x66) = 0x600;
    }

    addend = FIELD(arg0, u16, 0x66) + 0x80;
    FIELD(p2, u16, 0x1A) = FIELD(p2, u16, 0x1A) + addend;
    FIELD(p2, volatile u16, 0x1A) =
        FIELD(p2, volatile u16, 0x1A) & 0xFFF;
    ASM_KEEP(p2);

epilogue:
    return;
}

/* MECHANISM: TRUE-space local joins keep the 0x20 frame and s0/s1/s2 pointer ABI.
   cdk-G0 preserves D_80083780 in a1; D_800814A0 remains a direct scalar RMW.
   Guarded p1/s1, p2/s2, arg1_x/v1, and arg1_y/a0 roles close the coloring.
   Narrowed dx, input-only dx/dx_ok uses, and a volatile tail reread close scheduling. */
