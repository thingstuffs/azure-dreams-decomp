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

void func_8196BFB0(void *arg0, void *arg1, void *arg2)
{
    s32 height;
    s16 x;
    s16 z;
    s32 collide_x;
    s32 collide_y;
    s32 collide_z;
    u8 *camera;

    ((S_8196BFB0_0 *)arg1)->unk_00.at00.v += ((S_8196BFB0_1 *)arg0)->unk_8C;
    ((S_8196BFB0_1 *)arg0)->unk_8C += ((S_8196BFB0_1 *)arg0)->unk_98;
    collide_x = ((S_8196BFB0_0 *)arg1)->unk_00.at02.v;
    collide_y = ((S_8196BFB0_0 *)arg1)->unk_04.at02.v;
    collide_z = ((S_8196BFB0_0 *)arg1)->unk_08.at02.v;
    D_800269B4 = 1;
    if ((s16)func_800A45D8(collide_x, collide_y, collide_z) != 0) {
        ((S_8196BFB0_0 *)arg1)->unk_00.at00.v -= ((S_8196BFB0_1 *)arg0)->unk_8C;
        ((S_8196BFB0_1 *)arg0)->unk_8C = 0;
        ((S_8196BFB0_1 *)arg0)->unk_98 = 0;
    }

    ((S_8196BFB0_0 *)arg1)->unk_04.at00.v += ((S_8196BFB0_1 *)arg0)->unk_90;
    ((S_8196BFB0_1 *)arg0)->unk_90 += ((S_8196BFB0_1 *)arg0)->unk_9C;
    if ((s16)func_800A45D8(((S_8196BFB0_0 *)arg1)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)arg1)->unk_04.at02.v,
                           ((S_8196BFB0_0 *)arg1)->unk_08.at02.v) != 0) {
        ((S_8196BFB0_0 *)arg1)->unk_04.at00.v -= ((S_8196BFB0_1 *)arg0)->unk_90;
        ((S_8196BFB0_1 *)arg0)->unk_90 = 0;
        ((S_8196BFB0_1 *)arg0)->unk_9C = 0;
    }

    ((S_8196BFB0_0 *)arg1)->unk_08.at00.v += ((S_8196BFB0_1 *)arg0)->unk_94;
    ((S_8196BFB0_1 *)arg0)->unk_94 += ((S_8196BFB0_1 *)arg0)->unk_A0;

    height = ((S_8196BFB0_0 *)arg1)->unk_08.at02.v;
    if ((s16)func_800BCB04(((S_8196BFB0_0 *)arg1)->unk_00.at02.v,
                           ((S_8196BFB0_0 *)arg1)->unk_04.at02.v,
                           (s16)(((S_8196BFB0_0 *)arg1)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_8196BFB0_1 *)arg0)->unk_94 = 0;
        ((S_8196BFB0_1 *)arg0)->unk_90 = 0;
        ((S_8196BFB0_1 *)arg0)->unk_8C = 0;
        ((S_8196BFB0_0 *)arg1)->unk_08.at02.v =
            func_800BCB04(((S_8196BFB0_0 *)arg1)->unk_00.at02.v,
                          ((S_8196BFB0_0 *)arg1)->unk_04.at02.v,
                          (s16)(((S_8196BFB0_0 *)arg1)->unk_08.at02p.v - 4)) - 0x11;
        ((S_8196BFB0_0 *)arg1)->unk_08.at00u.v = 0;
        ((S_8196BFB0_1 *)arg0)->unk_2C = 0;
    }

    if (((S_8196BFB0_1 *)arg0)->unk_50++ >= 3) {
        x = ((S_8196BFB0_2 *)arg2)->unk_1C.u;
        z = ((S_8196BFB0_2 *)arg2)->unk_1E.u;
        x = x - 0x100;
        if (x < 0) {
            x = 0;
        }
        z = z - 0x100;
        if (z < 0) {
            z = 0;
        }
        ((S_8196BFB0_2 *)arg2)->unk_1C.s = x;
        ((S_8196BFB0_2 *)arg2)->unk_1E.s = z;
    }

    camera = D_80083780;
    func_80024AF8(arg0, arg1, arg2,
                  (s16)(((S_8196BFB0_0 *)arg1)->unk_00.at02.v - ((S_8196BFB0_3 *)camera)->unk_02),
                  (s16)(((S_8196BFB0_0 *)arg1)->unk_04.at02.v - ((S_8196BFB0_3 *)camera)->unk_06),
                  (s16)(((S_8196BFB0_0 *)arg1)->unk_08.at02p.v - ((S_8196BFB0_3 *)camera)->unk_0A));

    if (--((S_8196BFB0_1 *)arg0)->unk_2C <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

    if (((S_8196BFB0_2 *)arg2)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
