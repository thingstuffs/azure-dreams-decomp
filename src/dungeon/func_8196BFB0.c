#include "common.h"

typedef struct S_8196BFB0_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; volatile u16 v; } at02u; struct { u8 pad[0x2]; u16 v; } at02p; } unk_08;   /* overlapping accesses */
} S_8196BFB0_0;   /* arg1 in func_8196BFB0 */

typedef struct S_8196BFB0_1 {
    u8 pad_00[0x2C];
    s16 unk_2C;
    u8 pad_2E[0x22];
    s16 unk_50;
    u8 pad_52[0x3A];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196BFB0_1;   /* arg0 in func_8196BFB0 */

typedef struct S_8196BFB0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
} S_8196BFB0_2;   /* arg2 in func_8196BFB0 */

typedef struct S_8196BFB0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8196BFB0_3;   /* camera in func_8196BFB0 */



extern void func_80024AF8(void *arg0, void *arg1, void *arg2,
                          s16 arg3, s16 arg4, s16 arg5);
extern s32 func_800A45D8(u16 arg0, u16 arg1, s16 arg2);
extern s16 func_800BCB04(u16 arg0, u16 arg1, s16 arg2);

extern s16 D_800269B4;
extern s32 D_800814A0;
extern u8 D_80083780[];

/* Updates and renders a shrinking object with collision and lifetime checks. */
void func_8196BFB0(void *object, void *position, void *render_state)
{
    s32 height;
    s16 scale_x;
    s16 scale_y;
    s32 collide_x;
    s32 collide_y;
    s32 collide_z;
    u8 *camera;

    ((S_8196BFB0_0 *)position)->unk_00.at00.v += ((S_8196BFB0_1 *)object)->unk_8C;
    ((S_8196BFB0_1 *)object)->unk_8C += ((S_8196BFB0_1 *)object)->unk_98;
    collide_x = ((S_8196BFB0_0 *)position)->unk_00.at02.v;
    collide_y = ((S_8196BFB0_0 *)position)->unk_04.at02.v;
    collide_z = ((S_8196BFB0_0 *)position)->unk_08.at02.v;
    D_800269B4 = 1;
    if ((s16)func_800A45D8(collide_x, collide_y, collide_z) != 0) {
        ((S_8196BFB0_0 *)position)->unk_00.at00.v -= ((S_8196BFB0_1 *)object)->unk_8C;
        ((S_8196BFB0_1 *)object)->unk_8C = 0;
        ((S_8196BFB0_1 *)object)->unk_98 = 0;
    }

    ((S_8196BFB0_0 *)position)->unk_04.at00.v += ((S_8196BFB0_1 *)object)->unk_90;
    ((S_8196BFB0_1 *)object)->unk_90 += ((S_8196BFB0_1 *)object)->unk_9C;
    if ((s16)func_800A45D8(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_08.at02.v) != 0) {
        ((S_8196BFB0_0 *)position)->unk_04.at00.v -= ((S_8196BFB0_1 *)object)->unk_90;
        ((S_8196BFB0_1 *)object)->unk_90 = 0;
        ((S_8196BFB0_1 *)object)->unk_9C = 0;
    }

    ((S_8196BFB0_0 *)position)->unk_08.at00.v += ((S_8196BFB0_1 *)object)->unk_94;
    ((S_8196BFB0_1 *)object)->unk_94 += ((S_8196BFB0_1 *)object)->unk_A0;

    height = ((S_8196BFB0_0 *)position)->unk_08.at02.v;
    if ((s16)func_800BCB04(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                           (s16)(((S_8196BFB0_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_8196BFB0_1 *)object)->unk_94 = 0;
        ((S_8196BFB0_1 *)object)->unk_90 = 0;
        ((S_8196BFB0_1 *)object)->unk_8C = 0;
        ((S_8196BFB0_0 *)position)->unk_08.at02.v =
            func_800BCB04(((S_8196BFB0_0 *)position)->unk_00.at02.v,
                          ((S_8196BFB0_0 *)position)->unk_04.at02.v,
                          (s16)(((S_8196BFB0_0 *)position)->unk_08.at02p.v - 4)) - 0x11;
        ((S_8196BFB0_0 *)position)->unk_08.at00u.v = 0;
        ((S_8196BFB0_1 *)object)->unk_2C = 0;
    }

    if (((S_8196BFB0_1 *)object)->unk_50++ >= 3) {
        scale_x = ((S_8196BFB0_2 *)render_state)->unk_1C.u;
        scale_y = ((S_8196BFB0_2 *)render_state)->unk_1E.u;
        scale_x = scale_x - 0x100;
        if (scale_x < 0) {
            scale_x = 0;
        }
        scale_y = scale_y - 0x100;
        if (scale_y < 0) {
            scale_y = 0;
        }
        ((S_8196BFB0_2 *)render_state)->unk_1C.s = scale_x;
        ((S_8196BFB0_2 *)render_state)->unk_1E.s = scale_y;
    }

    camera = D_80083780;
    func_80024AF8(object, position, render_state,
                  (s16)(((S_8196BFB0_0 *)position)->unk_00.at02.v - ((S_8196BFB0_3 *)camera)->unk_02),
                  (s16)(((S_8196BFB0_0 *)position)->unk_04.at02.v - ((S_8196BFB0_3 *)camera)->unk_06),
                  (s16)(((S_8196BFB0_0 *)position)->unk_08.at02p.v - ((S_8196BFB0_3 *)camera)->unk_0A));

    if (--((S_8196BFB0_1 *)object)->unk_2C <= 0) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (((S_8196BFB0_2 *)render_state)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
