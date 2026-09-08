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

/* Updates a spiraling effect's growth, motion, and fade-out. */
void func_81952B4C(void *effect, void *position, void *sprite)
{
    s16 state;
    s16 radius;
    s16 frames_left;
    s32 velocity_x;
    s32 velocity_y;
    s32 global_flags;
    u16 scale;
    u8 brightness;

    D_800249A6++;

    if (D_800249A4 != 0 && ((S_81952B4C_0 *)effect)->unk_24.s < 2) {
        ((S_81952B4C_0 *)effect)->unk_00 =
            func_80064584(((S_81952B4C_0 *)effect)->unk_28.s) *
            ((S_81952B4C_0 *)effect)->unk_34 * 8;
        ((S_81952B4C_0 *)effect)->unk_04 =
            func_800644B8(((S_81952B4C_0 *)effect)->unk_28.s) *
            ((S_81952B4C_0 *)effect)->unk_34 * 8;
        ((S_81952B4C_0 *)effect)->unk_24.s = 2;
    }

    ((S_81952B4C_1 *)position)->unk_0E = ((S_81952B4C_1 *)position)->unk_00.at02.v;
    ((S_81952B4C_1 *)position)->unk_12 = ((S_81952B4C_1 *)position)->unk_04.at02.v;
    ((S_81952B4C_1 *)position)->unk_16 = ((S_81952B4C_1 *)position)->unk_08.at02.v;

    state = ((S_81952B4C_0 *)effect)->unk_24.s;
    if (state == 1) {
        goto move;
    }
    if (state < 2) {
        if (state == 0) {
            goto grow;
        }
        func_800245F0();
        return;
    }
    if (state == 2) {
        goto fade_out;
    }
    func_800245F0();
    return;

grow:
    scale = ((S_81952B4C_2 *)sprite)->unk_1E;
    scale += (0x1000 - scale) / ((S_81952B4C_0 *)effect)->unk_2C;
    ((S_81952B4C_2 *)sprite)->unk_1E = scale;
    ((S_81952B4C_2 *)sprite)->unk_1C = scale;
    if (scale >= 0x801) {
        ((S_81952B4C_2 *)sprite)->unk_1E = 0x800;
        ((S_81952B4C_2 *)sprite)->unk_1C = 0x800;
    }

    brightness = ((S_81952B4C_2 *)sprite)->unk_0C.at02.v + 2;
    ((S_81952B4C_2 *)sprite)->unk_0C.at02.v = brightness;
    ((S_81952B4C_2 *)sprite)->unk_0C.at01.v = brightness;
    ((S_81952B4C_2 *)sprite)->unk_0C.at00.v = brightness;
    if (brightness >= 0x81) {
        ((S_81952B4C_2 *)sprite)->unk_0C.at00u.v = 0x00808080;
    }

    ((S_81952B4C_1 *)position)->unk_00.at00.v =
        (((S_81952B4C_0 *)effect)->unk_10 << 16) +
        func_80064584(((S_81952B4C_0 *)effect)->unk_28.s) *
        ((S_81952B4C_0 *)effect)->unk_34 * 8;
    ((S_81952B4C_1 *)position)->unk_04.at00.v =
        (((S_81952B4C_0 *)effect)->unk_12 << 16) +
        func_800644B8(((S_81952B4C_0 *)effect)->unk_28.s) *
        ((S_81952B4C_0 *)effect)->unk_34 * 8;

    ((S_81952B4C_0 *)effect)->unk_08 -= 0x5000;
    radius = (u16)((S_81952B4C_0 *)effect)->unk_34 + 4;
    ((S_81952B4C_0 *)effect)->unk_34 = radius;
    if (radius >= 0x41) {
        ((S_81952B4C_0 *)effect)->unk_34 = 0x40;
    }

    ((S_81952B4C_0 *)effect)->unk_28.u += 0x180;
    frames_left = (u16)((S_81952B4C_0 *)effect)->unk_2C - 1;
    ((S_81952B4C_0 *)effect)->unk_2C = frames_left;
    if ((frames_left << 16) <= 0) {
        ((S_81952B4C_0 *)effect)->unk_24.u++;
        func_800245F0();
        return;
    }
    goto move;

fade_out:
    velocity_x = ((S_81952B4C_0 *)effect)->unk_00;
    velocity_y = ((S_81952B4C_0 *)effect)->unk_04;
    ((S_81952B4C_0 *)effect)->unk_00 = velocity_x + (velocity_x >> 1);
    ((S_81952B4C_0 *)effect)->unk_04 = velocity_y + (velocity_y >> 1);
    ((S_81952B4C_0 *)effect)->unk_08 += 0x10000;

    brightness = ((S_81952B4C_2 *)sprite)->unk_0C.at02.v - 4;
    ((S_81952B4C_2 *)sprite)->unk_0C.at02.v = brightness;
    ((S_81952B4C_2 *)sprite)->unk_0C.at01.v = brightness;
    ((S_81952B4C_2 *)sprite)->unk_0C.at00.v = brightness;
    if ((s8)brightness > 0) {
        goto move;
    }

    (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
    global_flags = D_800814A0 | 0x8000;
    ((S_81952B4C_0 *)effect)->unk_24.u++;
    D_800814A0 = global_flags;
    func_80024638();
    return;

move:
    ((S_81952B4C_0 *)effect)->unk_2A++;
    ((S_81952B4C_1 *)position)->unk_00.at00.v += ((S_81952B4C_0 *)effect)->unk_00;
    ((S_81952B4C_1 *)position)->unk_04.at00.v += ((S_81952B4C_0 *)effect)->unk_04;
    ((S_81952B4C_1 *)position)->unk_08.at00.v += ((S_81952B4C_0 *)effect)->unk_08;
}
