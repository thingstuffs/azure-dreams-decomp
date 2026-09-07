#include "common.h"

typedef struct S_81952B4C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x10];
    union { s16 s; u16 u; } unk_24;   /* accessed as both */
    u8 pad_26[0x2];
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x6];
    s16 unk_34;
} S_81952B4C_0;   /* arg0 in func_81952B4C */

typedef struct S_81952B4C_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_81952B4C_1;   /* arg1 in func_81952B4C */

typedef struct S_81952B4C_2 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
} S_81952B4C_2;   /* arg2 in func_81952B4C */



extern void func_800245F0(void) __attribute__((noreturn));
extern void func_80024638(void) __attribute__((noreturn));
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

extern s16 D_800249A4;
extern u16 D_800249A6;
extern s32 D_800814A0;

void func_81952B4C(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s16 angle;
    s16 life;
    s32 x;
    s32 y;
    s32 flags;
    u16 scale;
    u8 color;

    D_800249A6++;

    if (D_800249A4 != 0 && ((S_81952B4C_0 *)arg0)->unk_24.s < 2) {
        ((S_81952B4C_0 *)arg0)->unk_00 =
            func_80064584(((S_81952B4C_0 *)arg0)->unk_28.s) *
            ((S_81952B4C_0 *)arg0)->unk_34 * 8;
        ((S_81952B4C_0 *)arg0)->unk_04 =
            func_800644B8(((S_81952B4C_0 *)arg0)->unk_28.s) *
            ((S_81952B4C_0 *)arg0)->unk_34 * 8;
        ((S_81952B4C_0 *)arg0)->unk_24.s = 2;
    }

    ((S_81952B4C_1 *)arg1)->unk_0E = ((S_81952B4C_1 *)arg1)->unk_00.at02.v;
    ((S_81952B4C_1 *)arg1)->unk_12 = ((S_81952B4C_1 *)arg1)->unk_04.at02.v;
    ((S_81952B4C_1 *)arg1)->unk_16 = ((S_81952B4C_1 *)arg1)->unk_08.at02.v;

    state = ((S_81952B4C_0 *)arg0)->unk_24.s;
    if (state == 1) {
        goto update;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        func_800245F0();
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    func_800245F0();
    return;

state_zero:
    scale = ((S_81952B4C_2 *)arg2)->unk_1E;
            scale += (0x1000 - scale) / ((S_81952B4C_0 *)arg0)->unk_2C;
            ((S_81952B4C_2 *)arg2)->unk_1E = scale;
            ((S_81952B4C_2 *)arg2)->unk_1C = scale;
            if (scale >= 0x801) {
                ((S_81952B4C_2 *)arg2)->unk_1E = 0x800;
                ((S_81952B4C_2 *)arg2)->unk_1C = 0x800;
            }

            color = ((S_81952B4C_2 *)arg2)->unk_0C.at02.v + 2;
            ((S_81952B4C_2 *)arg2)->unk_0C.at02.v = color;
            ((S_81952B4C_2 *)arg2)->unk_0C.at01.v = color;
            ((S_81952B4C_2 *)arg2)->unk_0C.at00.v = color;
            if (color >= 0x81) {
                ((S_81952B4C_2 *)arg2)->unk_0C.at00u.v = 0x00808080;
            }

            ((S_81952B4C_1 *)arg1)->unk_00.at00.v =
                (((S_81952B4C_0 *)arg0)->unk_10 << 16) +
                func_80064584(((S_81952B4C_0 *)arg0)->unk_28.s) *
                ((S_81952B4C_0 *)arg0)->unk_34 * 8;
            ((S_81952B4C_1 *)arg1)->unk_04.at00.v =
                (((S_81952B4C_0 *)arg0)->unk_12 << 16) +
                func_800644B8(((S_81952B4C_0 *)arg0)->unk_28.s) *
                ((S_81952B4C_0 *)arg0)->unk_34 * 8;

            ((S_81952B4C_0 *)arg0)->unk_08 -= 0x5000;
            angle = (u16)((S_81952B4C_0 *)arg0)->unk_34 + 4;
            ((S_81952B4C_0 *)arg0)->unk_34 = angle;
            if (angle >= 0x41) {
                ((S_81952B4C_0 *)arg0)->unk_34 = 0x40;
            }

            ((S_81952B4C_0 *)arg0)->unk_28.u += 0x180;
            life = (u16)((S_81952B4C_0 *)arg0)->unk_2C - 1;
            ((S_81952B4C_0 *)arg0)->unk_2C = life;
            if ((life << 16) <= 0) {
                ((S_81952B4C_0 *)arg0)->unk_24.u++;
                func_800245F0();
                return;
            }
    goto update;

state_two:
        x = ((S_81952B4C_0 *)arg0)->unk_00;
        y = ((S_81952B4C_0 *)arg0)->unk_04;
        ((S_81952B4C_0 *)arg0)->unk_00 = x + (x >> 1);
        ((S_81952B4C_0 *)arg0)->unk_04 = y + (y >> 1);
        ((S_81952B4C_0 *)arg0)->unk_08 += 0x10000;

        color = ((S_81952B4C_2 *)arg2)->unk_0C.at02.v - 4;
        ((S_81952B4C_2 *)arg2)->unk_0C.at02.v = color;
        ((S_81952B4C_2 *)arg2)->unk_0C.at01.v = color;
        ((S_81952B4C_2 *)arg2)->unk_0C.at00.v = color;
        if ((s8)color > 0) {
            goto update;
        }

        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        flags = D_800814A0 | 0x8000;
        ((S_81952B4C_0 *)arg0)->unk_24.u++;
        D_800814A0 = flags;
        func_80024638();
        return;

update:
    ((S_81952B4C_0 *)arg0)->unk_2A++;
    ((S_81952B4C_1 *)arg1)->unk_00.at00.v += ((S_81952B4C_0 *)arg0)->unk_00;
    ((S_81952B4C_1 *)arg1)->unk_04.at00.v += ((S_81952B4C_0 *)arg0)->unk_04;
    ((S_81952B4C_1 *)arg1)->unk_08.at00.v += ((S_81952B4C_0 *)arg0)->unk_08;
}
