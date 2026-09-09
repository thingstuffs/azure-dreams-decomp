#include "common.h"


extern s32 func_800C30E0(void *arg0, void *arg1, void *arg2);
extern s16 func_800C2B38(void *arg0, s32 arg1, s32 arg2);
extern void func_800C37C4(void *arg0, void *arg1, void *arg2);
extern int abs(int);

extern s32 D_800D4FE8[4];
extern s32 D_800D4FF8[4];
extern s32 D_800D5008[4];
extern s32 D_800D5018[4];


typedef struct S_800C355C_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800C355C_0;   /* arg1 in func_800C355C */

typedef struct S_800C355C_1 {
    u8 pad_00[0x72];
    s16 unk_72;
    u8 pad_74[0x10];
    union { s16 s; u16 u; } unk_84;   /* accessed as both */
    union { s16 s; u16 u; } unk_86;   /* accessed as both */
    u8 pad_88[0x4];
    union { s16 s; u16 u; } unk_8C;   /* accessed as both */
    union { s16 s; u16 u; } unk_8E;   /* accessed as both */
} S_800C355C_1;   /* arg0 in func_800C355C */

void func_800C355C(S_800C355C_1 *arg0, void *arg1, void *arg2)
{
    s32 pos_x;
    register s32 step_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 pos_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    ((S_800C355C_0 *)arg1)->unk_00.at00.v = pos_x;
    ((S_800C355C_0 *)arg1)->unk_04.at00.v = pos_y;
    ((S_800C355C_0 *)arg1)->unk_0A = func_800C2B38(arg1, step_x, step_y);

    angle = 0x400 - arg0->unk_72;
    quadrant = (angle / 0x400) & 3;

    if (quadrant == 1) {
        goto case_one;
    }
    if (quadrant < 2) {
        if (quadrant == 0) {
            goto case_zero;
        }
        goto case_three;
    }
    if (quadrant == 2) {
        goto case_two;
    }
    goto case_three;

case_zero:
    if (arg0->unk_84.s + arg0->unk_8C.s < ((S_800C355C_0 *)arg1)->unk_00.at02.v) {
        register u16 bound_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 bound_y ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 bound_sum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        bound_x = arg0->unk_84.u;
        bound_y = arg0->unk_8C.u;
        bound_sum = bound_y + bound_x;
        ((S_800C355C_0 *)arg1)->unk_00.at02u.v = bound_sum;
        goto case_zero_call;
    }
    goto apply;

case_zero_call:
    goto clamp;

case_one:
    if (arg0->unk_86.s + arg0->unk_8E.s < ((S_800C355C_0 *)arg1)->unk_04.at02.v) {
        ((S_800C355C_0 *)arg1)->unk_04.at02u.v = arg0->unk_86.u + arg0->unk_8E.u;
        goto clamp;
    }
    goto apply;

case_two:
    if (((S_800C355C_0 *)arg1)->unk_00.at02.v < arg0->unk_84.s - arg0->unk_8C.s) {
        u16 bound_x;
        u16 bound_y;
        bound_x = arg0->unk_84.u;
        bound_y = arg0->unk_8C.u;
        ((S_800C355C_0 *)arg1)->unk_00.at02u.v = bound_x - bound_y;
        goto clamp;
    }
    goto apply;

case_three:
    if (((S_800C355C_0 *)arg1)->unk_04.at02.v < arg0->unk_86.s - arg0->unk_8E.s) {
        u16 bound_x;
        u16 bound_y;
        bound_x = arg0->unk_86.u;
        bound_y = arg0->unk_8E.u;
        ((S_800C355C_0 *)arg1)->unk_04.at02u.v = bound_x - bound_y;
    } else {
        goto apply;
    }

clamp:
    func_800C37C4(arg0, arg1, arg2);
    return;

apply:
    limit = 0x20000;

    value = ((S_800C355C_0 *)arg1)->unk_0C + D_800D4FE8[quadrant];
    ((S_800C355C_0 *)arg1)->unk_0C = value;
    value = abs(value);
    value = limit < value;
    if (value != 0) {
        ((S_800C355C_0 *)arg1)->unk_0C = D_800D4FF8[quadrant];
    }

    value = ((S_800C355C_0 *)arg1)->unk_10 + D_800D5008[quadrant];
    ((S_800C355C_0 *)arg1)->unk_10 = value;
    value = abs(value);
    value = limit < value;
    if (value != 0) {
        ((S_800C355C_0 *)arg1)->unk_10 = D_800D5018[quadrant];
    }
}
