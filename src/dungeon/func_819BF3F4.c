#include "common.h"

typedef struct S_80024BF4_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_80024BF4_0;   /* scratch in func_80024BF4 */

typedef struct S_80024BF4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024BF4_1;   /* arg1 in func_80024BF4 */

typedef struct S_80024BF4_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_80024BF4_2;   /* arg2 in func_80024BF4 */

typedef struct S_80024BF4_3 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80024BF4_3;   /* *(u8 **)D_80083160 in func_80024BF4 */

typedef struct S_80024BF4_4 {
    u8 pad_00[0xC];
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u32 unk_18;
    u8 pad_1C[0x1E];
    u8 unk_3A;
    u8 unk_3B;
    u16 unk_3C;
    u8 unk_3E;
    u8 unk_3F;
    u16 unk_40;
    u8 pad_42[0x2];
    u8 unk_44;
    u8 unk_45;
    u8 unk_46;
    u8 unk_47;
    u8 pad_48[0x2];
    u16 unk_4A;
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
} S_80024BF4_4;   /* arg0 in func_80024BF4 */

typedef struct S_80024BF4_5 {
    u32 unk_00;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u32 unk_10;
    u16 unk_14;
    u16 unk_16;
    u8 unk_18;
    u8 unk_19;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u32 unk_28;
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} S_80024BF4_5;   /* packet in func_80024BF4 */



typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006671C(void *);
extern u8 D_80083160[];

void func_80024BF4(S_80024BF4_4 *arg0, S_80024BF4_1 *arg1, S_80024BF4_2 *arg2, s16 arg3)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 index;
    u16 flags;
    u8 texFlags;
    MATRIX matrix;

    ((S_80024BF4_0 *)scratch)->unk_24.p = *(u8 **)D_80083160 + 0xB0;
    ((S_80024BF4_0 *)scratch)->unk_88 = arg1->unk_02;
    ((S_80024BF4_0 *)scratch)->unk_8C = arg1->unk_06;
    ((S_80024BF4_0 *)scratch)->unk_90 = arg1->unk_0A;
    arg2->unk_14 |= 0x8000;

    func_800649A0();

    ((S_80024BF4_0 *)scratch)->unk_3C = 0x2000;
    ((S_80024BF4_0 *)scratch)->unk_38 = 0x2000;
    ((S_80024BF4_0 *)scratch)->unk_34 = 0x2000;
    ((S_80024BF4_0 *)scratch)->unk_A4 = arg2->unk_16;
    ((S_80024BF4_0 *)scratch)->unk_A8 = arg2->unk_1A;
    ((S_80024BF4_0 *)scratch)->unk_A6 = arg2->unk_18;
    func_80065820(scratch + 0xA4, scratch + 0x74);
    func_80064AE0(&matrix);
    func_80064840(&matrix, scratch + 0x74, scratch + 0x54);
    func_80064BC0(scratch + 0x54, scratch + 0x34);
    func_80064D80(scratch + 0x54);
    func_80064CF0(scratch + 0x54);

    texture = arg2->unk_08;
    ((S_80024BF4_0 *)scratch)->unk_28 = arg2->unk_14;
    packet = ((S_80024BF4_3 *)(*(u8 **)D_80083160))->unk_8D0;
    ((S_80024BF4_3 *)(*(u8 **)D_80083160))->unk_8D0 = packet + 0x34;

    ((S_80024BF4_0 *)scratch)->unk_B0 = arg0->unk_4A;
    ((S_80024BF4_0 *)scratch)->unk_B8 = arg0->unk_50;
    ((S_80024BF4_0 *)scratch)->unk_C0 = arg0->unk_56;
    ((S_80024BF4_0 *)scratch)->unk_C8 = arg0->unk_5C;
    ((S_80024BF4_0 *)scratch)->unk_B2 = arg0->unk_4C;
    ((S_80024BF4_0 *)scratch)->unk_BA = arg0->unk_52;
    ((S_80024BF4_0 *)scratch)->unk_C2 = arg0->unk_58;
    ((S_80024BF4_0 *)scratch)->unk_CA = arg0->unk_5E;
    ((S_80024BF4_0 *)scratch)->unk_B4 = arg0->unk_4E;
    ((S_80024BF4_0 *)scratch)->unk_BC = arg0->unk_54;
    ((S_80024BF4_0 *)scratch)->unk_C4 = arg0->unk_5A;
    ((S_80024BF4_0 *)scratch)->unk_CC = arg0->unk_60;

    index = func_80065590(scratch + 0xB0, scratch + 0xB8,
                          scratch + 0xC0, scratch + 0xC8,
                          packet + 8, packet + 0x14,
                          packet + 0x20, packet + 0x2C,
                          scratch + 0xD0, scratch + 0xD4) - arg3 - 6;
    ((S_80024BF4_0 *)scratch)->unk_100 = index;

    if ((u32)index < 0x1E0) {
        if ((((u16)(((S_80024BF4_5 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((S_80024BF4_5 *)packet)->unk_14 + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_16 + 0x20) < 0x121)) |
            (((u16)(((S_80024BF4_5 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_22 + 0x20) < 0x121)) |
            (((u16)(((S_80024BF4_5 *)packet)->unk_2C + 0x20) < 0x181) &&
             ((u16)(((S_80024BF4_5 *)packet)->unk_2E + 0x20) < 0x121))) {
            arg2->unk_14 &= 0x7FFF;
            ((S_80024BF4_5 *)packet)->unk_0E = arg0->unk_3C;
            ((S_80024BF4_5 *)packet)->unk_1A = arg0->unk_40;
            ((S_80024BF4_5 *)packet)->unk_0C = arg0->unk_3A;
            ((S_80024BF4_5 *)packet)->unk_18 = arg0->unk_3E;
            ((S_80024BF4_5 *)packet)->unk_24 = arg0->unk_44;
            ((S_80024BF4_5 *)packet)->unk_30 = arg0->unk_46;
            ((S_80024BF4_5 *)packet)->unk_0D = arg0->unk_3B;
            ((S_80024BF4_5 *)packet)->unk_19 = arg0->unk_3F;
            ((S_80024BF4_5 *)packet)->unk_25 = arg0->unk_45;
            ((S_80024BF4_5 *)packet)->unk_31 = arg0->unk_47;
            ((S_80024BF4_5 *)packet)->unk_04.at00.v = arg0->unk_0C;
            ((S_80024BF4_5 *)packet)->unk_10 = arg0->unk_10;
            ((S_80024BF4_5 *)packet)->unk_1C = arg0->unk_14;
            ((S_80024BF4_5 *)packet)->unk_28 = arg0->unk_18;

            func_8006671C(packet);

            texFlags = texture[1];
            arg2->unk_0F = texFlags;
            flags = ((S_80024BF4_0 *)scratch)->unk_28;
            if (flags & 8) {
                arg2->unk_0F = (flags & 4) ?
                    (texFlags | 2) : (texFlags & 0xFD);
            }

            ((S_80024BF4_5 *)packet)->unk_04.at03.v |= arg2->unk_0F;
            ((S_80024BF4_5 *)packet)->unk_00 = (((S_80024BF4_5 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((S_80024BF4_0 *)scratch)->unk_24.p2) + ((S_80024BF4_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);

            (*(u32 *)((u8 *)(((S_80024BF4_0 *)scratch)->unk_24.p2) + ((S_80024BF4_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((S_80024BF4_0 *)scratch)->unk_24.p2) + ((S_80024BF4_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    func_80064A40();
}
