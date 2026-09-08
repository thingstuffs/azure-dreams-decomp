#include "common.h"

typedef struct S_800B9998_0 {
    u8 pad_00[0x66];
    union { u16 s; s16 u; } unk_66;   /* accessed as both */
    u8 pad_68[0x30];
    s8 * unk_98;
} S_800B9998_0;   /* arg0 in func_800B9998 */

typedef struct S_800B9998_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x6];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
} S_800B9998_1;   /* town in func_800B9998 */

typedef struct S_800B9998_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800B9998_2;   /* p1 in func_800B9998 */

typedef struct S_800B9998_3 {
    u8 pad_00[0x1A];
    union { u16 s; volatile u16 u; } unk_1A;   /* accessed as both */
} S_800B9998_3;   /* p2 in func_800B9998 */



extern s32 D_800814A0;
extern s32 D_80083780;

extern void func_80033D08(void *);
extern s32 func_8009CFE0(void *, void *);

void func_800B9998(void *arg0, void *arg1, void *arg2) {
    register u8 *p1 ASM_REG("$17") = arg1;   /* MATCH pin: load-bearing for the whole function shape */
    u8 *p2 = arg2;
    s8 *byte_ptr;
    u8 *town;
    s32 dx;
    s32 dy;
    s32 dx_ok;
    s32 sum;
    register s32 arg1_x ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 arg1_y;
    s32 angle;
    s32 raw_angle;
    s32 addend;

    if (func_8009CFE0(arg0, arg1) != 0) {
        byte_ptr = ((S_800B9998_0 *)arg0)->unk_98;
        if (byte_ptr != 0) {
            *byte_ptr = 0;
        }
        func_80033D08(arg0);
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        goto epilogue;
    }

    raw_angle = ((S_800B9998_0 *)arg0)->unk_66.s;
    angle = ((S_800B9998_0 *)arg0)->unk_66.u;
    if (angle >= 0x100) {
        ((S_800B9998_0 *)arg0)->unk_66.s = raw_angle - 0x20;
        goto angle_ready;
    }
    if (angle >= 0x10) {
        ((S_800B9998_0 *)arg0)->unk_66.s = raw_angle - 0x10;
        goto angle_ready;
    }
    ((S_800B9998_0 *)arg0)->unk_66.s = 0;

    angle_ready:
    town = (u8 *)&D_80083780;
    dx = ((S_800B9998_1 *)town)->unk_02;
    arg1_x = ((S_800B9998_2 *)p1)->unk_02;
    arg1_y = ((S_800B9998_2 *)p1)->unk_06;
    dx -= arg1_x;
    if (dx < 0) {
        dx = -dx;
    }
    dx = (s16)dx;
    dy = ((S_800B9998_1 *)town)->unk_06;
    dx_ok = dx < 0x81;
    ASM_USE(dx_ok);   /* MATCH pin: retail schedule: same instructions, different order without it */
    dy -= arg1_y;
    if (dy < 0) {
        dy = -dy;
    }

    if (dx_ok && ((s16)dy < 0x81)) {
        sum = (((S_800B9998_1 *)town)->unk_0E * ((S_800B9998_1 *)town)->unk_0E) +
              (((S_800B9998_1 *)town)->unk_12 * ((S_800B9998_1 *)town)->unk_12);
        ((S_800B9998_0 *)arg0)->unk_66.s =
            ((S_800B9998_0 *)arg0)->unk_66.s +
            ((s32)(sum + ((u32)sum >> 31)) >> 1);
    }

    if (((S_800B9998_0 *)arg0)->unk_66.u >= 0x601) {
        ((S_800B9998_0 *)arg0)->unk_66.s = 0x600;
    }

    addend = ((S_800B9998_0 *)arg0)->unk_66.s + 0x80;
    ((S_800B9998_3 *)p2)->unk_1A.s = ((S_800B9998_3 *)p2)->unk_1A.s + addend;
    ((S_800B9998_3 *)p2)->unk_1A.u =
        ((S_800B9998_3 *)p2)->unk_1A.u & 0xFFF;

epilogue:
    return;
}

/* MECHANISM: TRUE-space local joins keep the 0x20 frame and s0/s1/s2 pointer ABI.
   cdk-G0 preserves D_80083780 in a1; D_800814A0 remains a direct scalar RMW.
   Guarded p1/s1, p2/s2, arg1_x/v1, and arg1_y/a0 roles close the coloring.
   Narrowed dx, input-only dx/dx_ok uses, and a volatile tail reread close scheduling. */
