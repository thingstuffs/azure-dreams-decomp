#include "common.h"

typedef struct S_800CCDA0_0 {
    s32 unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    s16 unk_08;
    s16 unk_0A;
} S_800CCDA0_0;   /* arg0 in func_800CCDA0 */

typedef struct S_800CCDA0_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800CCDA0_1;   /* arg1 in func_800CCDA0 */

typedef struct S_800CCDA0_2 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_800CCDA0_2;   /* base in func_800CCDA0 */

typedef struct S_800CCDA0_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    union { u16 s; volatile u16 u; } unk_1A;   /* accessed as both */
} S_800CCDA0_3;   /* arg2 in func_800CCDA0 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8009CE1C(s32, s32, s32, s32, s32, s32, s32);
extern void func_800A56E0(s32);

extern s32 D_800814A0;
extern u8 D_80083160[];

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern u8 *D_800E3D7C;

/* Updates a bouncing effect's motion, rotation, and fading until its lifetime expires. */
void func_800CCDA0(void *effect, void *motion, void *sprite)
{
    u16 ticks_or_angle;
    u8 *direction_data;

    if (((S_800CCDA0_0 *)effect)->unk_04.s == 0) {
        ((S_800CCDA0_1 *)motion)->unk_14 += 0x20000;

        ticks_or_angle = ((S_800CCDA0_0 *)effect)->unk_06.s - 1;
        ((S_800CCDA0_0 *)effect)->unk_06.s = ticks_or_angle;
        if ((ticks_or_angle << 16) == 0) {
            func_800A56E0(0x701);
        }

        if (((S_800CCDA0_0 *)effect)->unk_0A < ((S_800CCDA0_1 *)motion)->unk_08.at02.v) {
            func_8009CE1C(((S_800CCDA0_0 *)effect)->unk_00, 10,
                          D_800E3D7C[0x11], 8,
                          (((S_800CCDA0_0 *)effect)->unk_08 << 25) >> 16, 0, 2);

            direction_data = D_80083160;
            ((S_800CCDA0_1 *)motion)->unk_14 = -((S_800CCDA0_1 *)motion)->unk_14;
            ((S_800CCDA0_1 *)motion)->unk_0C =
                func_80064584(((S_800CCDA0_2 *)direction_data)->unk_C8) << 8;
            ((S_800CCDA0_1 *)motion)->unk_10 =
                func_800644B8(((S_800CCDA0_2 *)direction_data)->unk_C8) << 8;

            ((S_800CCDA0_3 *)sprite)->unk_14 |= 0xC;
            ((S_800CCDA0_0 *)effect)->unk_06.s = 12;
            ((S_800CCDA0_0 *)effect)->unk_04.u++;
        }
    } else {
        u16 angle;
        s16 ticks_left;

        ((S_800CCDA0_1 *)motion)->unk_14 += 0x80000;
        angle = ((S_800CCDA0_3 *)sprite)->unk_1A.s;
        ticks_left = ((S_800CCDA0_0 *)effect)->unk_06.u;
        angle += (0x400 - angle) / ticks_left;
        ((S_800CCDA0_3 *)sprite)->unk_1A.s = angle;

        {
            u16 wobble_angle;

            ticks_or_angle = ((S_800CCDA0_0 *)effect)->unk_06.s;
            wobble_angle = ((S_800CCDA0_3 *)sprite)->unk_1A.u;
            if (ticks_or_angle & 1) {
                ticks_or_angle = wobble_angle + 0x100;
            } else {
                ticks_or_angle = wobble_angle - 0x100;
            }
            ((S_800CCDA0_3 *)sprite)->unk_1A.u = ticks_or_angle;
        }

        ((S_800CCDA0_3 *)sprite)->unk_0C -=
            ((S_800CCDA0_3 *)sprite)->unk_0C / ((S_800CCDA0_0 *)effect)->unk_06.u;
        ((S_800CCDA0_3 *)sprite)->unk_0D -=
            ((S_800CCDA0_3 *)sprite)->unk_0D / ((S_800CCDA0_0 *)effect)->unk_06.u;
        ((S_800CCDA0_3 *)sprite)->unk_0E -=
            ((S_800CCDA0_3 *)sprite)->unk_0E / ((S_800CCDA0_0 *)effect)->unk_06.u;

        ticks_or_angle = ((S_800CCDA0_0 *)effect)->unk_06.s - 1;
        ((S_800CCDA0_0 *)effect)->unk_06.s = ticks_or_angle;
        if ((ticks_or_angle << 16) == 0) {
            D_80083460.fieldA--;
            (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

    ((S_800CCDA0_1 *)motion)->unk_00 += ((S_800CCDA0_1 *)motion)->unk_0C;
    ((S_800CCDA0_1 *)motion)->unk_04 += ((S_800CCDA0_1 *)motion)->unk_10;
    ((S_800CCDA0_1 *)motion)->unk_08.at00.v += ((S_800CCDA0_1 *)motion)->unk_14;
}
