#include "common.h"

typedef struct S_8195FD40_0 {
    u8 pad_00[0x20];
    u32 unk_20;
    u8 pad_24[0xC];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x34];
    u32 unk_70;
    u16 unk_74;
    u8 pad_76[0x2];
    u32 unk_78;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u32 unk_80;
    u16 unk_84;
    u8 pad_86[0x2];
    u32 unk_88;
    u16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_8195FD40_0;   /* scratch in func_8195FD40 */

typedef struct S_8195FD40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195FD40_1;   /* arg1 in func_8195FD40 */

typedef struct S_8195FD40_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8195FD40_2;   /* *global in func_8195FD40 */

typedef struct S_8195FD40_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_8195FD40_3;   /* arg2 in func_8195FD40 */

typedef struct S_8195FD40_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    u8 unk_15;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    s8 unk_24;
    s8 unk_25;
} S_8195FD40_4;   /* packet in func_8195FD40 */

typedef struct S_8195FD40_5 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8195FD40_5;   /* texture in func_8195FD40 */

typedef struct S_8195FD40_6 {
    u32 unk_00;
} S_8195FD40_6;   /* (u8 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20) in func_8195FD40 */



extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u8 D_80083160[];

void func_8195FD40(s32 arg0, S_8195FD40_1 *arg1, S_8195FD40_3 *arg2, s16 arg3)
{
    s32 sp28[8];
    u8 *scratch = (u8 *)0x1F800000;
    u8 **global = (u8 **)D_80083160;
    s32 *temp_v1;
    s32 temp_a0;
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 acc1;
    s32 acc2;
    s8 temp_v0_3;
    s8 temp_v0_5;
    u32 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_4;
    u8 *packet;
    u8 *texture;

    (void)arg0;
    ((S_8195FD40_0 *)scratch)->unk_20 = *global + 0xB0;
    ((S_8195FD40_0 *)scratch)->unk_E4 = arg1->unk_02;
    ((S_8195FD40_0 *)scratch)->unk_E8 = arg1->unk_06;
    ((S_8195FD40_0 *)scratch)->unk_EC = arg1->unk_0A;
    packet = ((S_8195FD40_2 *)(*global))->unk_8D0;
    texture = arg2->unk_08;
    func_800649A0();

    ((S_8195FD40_0 *)scratch)->unk_30 = arg2->unk_1C * 2;
    ((S_8195FD40_0 *)scratch)->unk_34 = arg2->unk_1E * 2;
    ((S_8195FD40_0 *)scratch)->unk_38 = 0x2000;
    ((S_8195FD40_0 *)scratch)->unk_100 = arg2->unk_16;
    ((S_8195FD40_0 *)scratch)->unk_104 = arg2->unk_1A;
    ((S_8195FD40_0 *)scratch)->unk_102 = arg2->unk_18;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(&sp28);
    func_80064840(&sp28, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    ((S_8195FD40_0 *)scratch)->unk_78 = 0x20;
    ((S_8195FD40_0 *)scratch)->unk_88 = 0x200000;
    ((S_8195FD40_0 *)scratch)->unk_80 = 0x200000;
    ((S_8195FD40_0 *)scratch)->unk_70 = 0;
    ((S_8195FD40_0 *)scratch)->unk_8C = 0;
    ((S_8195FD40_0 *)scratch)->unk_84 = 0;
    ((S_8195FD40_0 *)scratch)->unk_7C = 0;
    ((S_8195FD40_0 *)scratch)->unk_74 = 0;
    temp_v0 = func_80065590(scratch + 0x70, scratch + 0x78,
                            scratch + 0x80, scratch + 0x88,
                            packet + 8, packet + 0x10,
                            packet + 0x18, packet + 0x20,
                            scratch + 0x90, scratch + 0x94) - arg3;
    ((S_8195FD40_0 *)scratch)->unk_C0 = temp_v0;

    if (temp_v0 < 0x1E0U) {
        f0 = 0;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_08 + 0x20) < 0x181U) {
            f0 = (u16)(((S_8195FD40_4 *)packet)->unk_0A + 0x20) < 0x121U;
        }
        f1 = 0;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_10 + 0x20) < 0x181U) {
            f1 = (u16)(((S_8195FD40_4 *)packet)->unk_12 + 0x20) < 0x121U;
        }
        f2 = 0;
        acc1 = f0 | f1;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_18 + 0x20) < 0x181U) {
            f2 = (u16)(((S_8195FD40_4 *)packet)->unk_1A + 0x20) < 0x121U;
        }
        f3 = 0;
        acc2 = acc1 | f2;
        if ((u16)(((S_8195FD40_4 *)packet)->unk_20 + 0x20) < 0x181U) {
            f3 = (u16)(((S_8195FD40_4 *)packet)->unk_22 + 0x20) < 0x121U;
        }

        if ((acc2 | f3) != 0) {
            temp_v0_2 = ((S_8195FD40_5 *)texture)->unk_08;
            ((S_8195FD40_4 *)packet)->unk_1C = temp_v0_2;
            ((S_8195FD40_4 *)packet)->unk_0C = temp_v0_2;
            temp_v0_3 = ((S_8195FD40_5 *)texture)->unk_08 + ((S_8195FD40_5 *)texture)->unk_0A;
            ((S_8195FD40_4 *)packet)->unk_24 = temp_v0_3;
            ((S_8195FD40_4 *)packet)->unk_14 = temp_v0_3;
            temp_v0_4 = ((S_8195FD40_5 *)texture)->unk_09;
            ((S_8195FD40_4 *)packet)->unk_15 = temp_v0_4;
            ((S_8195FD40_4 *)packet)->unk_0D = temp_v0_4;
            temp_v0_5 = ((S_8195FD40_5 *)texture)->unk_09 + ((S_8195FD40_5 *)texture)->unk_0B;
            ((S_8195FD40_4 *)packet)->unk_25 = temp_v0_5;
            ((S_8195FD40_4 *)packet)->unk_1D = temp_v0_5;
            ((S_8195FD40_4 *)packet)->unk_16 = ((S_8195FD40_5 *)texture)->unk_04;
            ((S_8195FD40_4 *)packet)->unk_04.at00.v = arg2->unk_0C;
            ((S_8195FD40_4 *)packet)->unk_00.at03.v = 9;
            ((S_8195FD40_4 *)packet)->unk_04.at03.v = 0x2C;
            if (arg2->unk_14 & 4) {
                ((S_8195FD40_4 *)packet)->unk_04.at03.v = 0x2E;
            }
            temp_a0 = (s32)packet & 0xFFFFFF;
            ((S_8195FD40_4 *)packet)->unk_00.at00.v = (((S_8195FD40_4 *)packet)->unk_00.at00.v & 0xFF000000) |
                (((S_8195FD40_6 *)((u8 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20)))->unk_00 & 0xFFFFFF);
            temp_v1 = (s32 *)((((S_8195FD40_0 *)scratch)->unk_C0 * 4) +
                              ((S_8195FD40_0 *)scratch)->unk_20);
            packet += 0x28;
            *temp_v1 = (*temp_v1 & 0xFF000000) | temp_a0;
        }
    }
    func_80064A40();
    ((S_8195FD40_2 *)(*global))->unk_8D0 = packet;
}
