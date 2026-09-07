#include "common.h"


extern u8 D_80083160[];
extern s16 func_80066460(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80065590(
    void *arg0, void *arg1, void *arg2, void *arg3,
    void *arg4, void *arg5, void *arg6, void *arg7,
    void *arg8, void *arg9);


typedef struct S_818B6F90_0 {
    u8 * unk_00;
    union { volatile s32 v; volatile u32 v2; } unk_04;   /* accessed as both */
    u8 pad_08[0x8];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    u8 pad_16[0x2];
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x2];
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    u8 pad_26[0x2];
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x2];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    u8 pad_6C[0x4];
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
} S_818B6F90_0;   /* scratch in func_818B6F90 */

typedef struct S_818B6F90_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_818B6F90_1;   /* base in func_818B6F90 */

typedef struct S_818B6F90_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x5];
    u8 unk_18;
    u8 unk_19;
    s16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x5];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
    u8 unk_2A;
    u8 pad_2B[0x1];
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} S_818B6F90_2;   /* packet in func_818B6F90 */

typedef struct S_818B6F90_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_818B6F90_3;   /* arg1 in func_818B6F90 */

s32 func_818B6F90(s32 arg0, u8 *arg1)
{
    u8 *base;
    u8 *packet;
    u8 *scratch;
    s32 xpos;
    s32 shade;
    register s16 tpage ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u32 *ot;
    u32 *ot2;
    u32 index;
    u32 index2;
    u32 otword;
    u8 *a70;
    u8 *a74;
    u8 *a78;
    u8 *a7C;
    u8 *a08;
    u8 *a0C;

    scratch = (u8 *)0x1F800000;
    base = *(u8 **)D_80083160;
    ((S_818B6F90_0 *)scratch)->unk_00 = base + 0xB0;
    packet = ((S_818B6F90_1 *)base)->unk_8D0;
    ((S_818B6F90_1 *)base)->unk_8D0 = packet + 0x34;
    ((S_818B6F90_2 *)packet)->unk_00.at03.v = 0x0C;
    ((S_818B6F90_2 *)packet)->unk_07 = 0x3E;

    tpage = func_80066460(0, 3, 0x300, 0x100);
    xpos = (arg0 << 16) >> 13;
    xpos += 0x80;
    a70 = scratch + 0x70;
    a74 = scratch + 0x74;
    a78 = scratch + 0x78;
    a7C = scratch + 0x7C;
    a08 = scratch + 0x08;
    a0C = scratch + 0x0C;

    ((S_818B6F90_2 *)packet)->unk_1A = tpage;
    tpage = 0x7DCF;
    shade = 0x40;
    ASM_KEEP_NV(shade);   /* MATCH pin: keeps a statement from moving across a call/branch */
    ((S_818B6F90_2 *)packet)->unk_0E = tpage;
    ((S_818B6F90_2 *)packet)->unk_18 = xpos | 7;
    ((S_818B6F90_2 *)packet)->unk_24 = xpos | 7;
    ((S_818B6F90_2 *)packet)->unk_0C = xpos;
    ((S_818B6F90_2 *)packet)->unk_0D = shade;
    ((S_818B6F90_2 *)packet)->unk_19 = shade;
    ((S_818B6F90_2 *)packet)->unk_25 = 0x7F;
    ((S_818B6F90_2 *)packet)->unk_30 = xpos;
    ((S_818B6F90_2 *)packet)->unk_31 = 0x7F;
    ((S_818B6F90_2 *)packet)->unk_04 = 0;
    ((S_818B6F90_2 *)packet)->unk_05 = 0;
    ((S_818B6F90_2 *)packet)->unk_06 = 0;
    ((S_818B6F90_2 *)packet)->unk_10 = 0;
    ((S_818B6F90_2 *)packet)->unk_11 = 0;
    ((S_818B6F90_2 *)packet)->unk_12 = 0;

    ((S_818B6F90_2 *)packet)->unk_1C = ((S_818B6F90_3 *)arg1)->unk_0C;
    ((S_818B6F90_2 *)packet)->unk_1D = ((S_818B6F90_3 *)arg1)->unk_0D;
    ((S_818B6F90_2 *)packet)->unk_1E = ((S_818B6F90_3 *)arg1)->unk_0E;
    ((S_818B6F90_2 *)packet)->unk_28 = ((S_818B6F90_3 *)arg1)->unk_0C;
    ((S_818B6F90_2 *)packet)->unk_29 = ((S_818B6F90_3 *)arg1)->unk_0D;
    ((S_818B6F90_2 *)packet)->unk_2A = ((S_818B6F90_3 *)arg1)->unk_0E;

    ((S_818B6F90_0 *)scratch)->unk_10 = ((S_818B6F90_0 *)scratch)->unk_30 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_18 = ((S_818B6F90_0 *)scratch)->unk_40 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_20 = ((S_818B6F90_0 *)scratch)->unk_50 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_28 = ((S_818B6F90_0 *)scratch)->unk_60 >> 16;

    ((S_818B6F90_0 *)scratch)->unk_12 = ((S_818B6F90_0 *)scratch)->unk_34 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_1A = ((S_818B6F90_0 *)scratch)->unk_44 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_22 = ((S_818B6F90_0 *)scratch)->unk_54 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_2A = ((S_818B6F90_0 *)scratch)->unk_64 >> 16;

    ((S_818B6F90_0 *)scratch)->unk_14 = ((S_818B6F90_0 *)scratch)->unk_38 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_1C = ((S_818B6F90_0 *)scratch)->unk_48 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_24 = ((S_818B6F90_0 *)scratch)->unk_58 >> 16;
    ((S_818B6F90_0 *)scratch)->unk_2C = ((S_818B6F90_0 *)scratch)->unk_68 >> 16;

    ((S_818B6F90_0 *)scratch)->unk_04.v = func_80065590(
        scratch + 0x10, scratch + 0x18, scratch + 0x20, scratch + 0x28,
        a70, a74, a78, a7C,
        a08, a0C);

    (*(u16 *)((u8 *)packet + (0x08))) = ((S_818B6F90_0 *)scratch)->unk_70;
    (*(u16 *)((u8 *)packet + (0x0A))) = ((S_818B6F90_0 *)scratch)->unk_72;
    (*(u16 *)((u8 *)packet + (0x14))) = ((S_818B6F90_0 *)scratch)->unk_74;
    (*(u16 *)((u8 *)packet + (0x16))) = ((S_818B6F90_0 *)scratch)->unk_76;
    (*(u16 *)((u8 *)packet + (0x20))) = ((S_818B6F90_0 *)scratch)->unk_78;
    (*(u16 *)((u8 *)packet + (0x22))) = ((S_818B6F90_0 *)scratch)->unk_7A;
    ((S_818B6F90_2 *)packet)->unk_2C = ((S_818B6F90_0 *)scratch)->unk_7C;
    ((S_818B6F90_2 *)packet)->unk_2E = ((S_818B6F90_0 *)scratch)->unk_7E;

    index = ((S_818B6F90_0 *)scratch)->unk_04.v2;
    if (index < 0x1E0) {
        ot = (*(u32 * volatile *)((u8 *)scratch + (0x00)));
        otword = ot[index];
        ((S_818B6F90_2 *)packet)->unk_00.at00.v =
            (((S_818B6F90_2 *)packet)->unk_00.at00.v & 0xFF000000) |
            (otword & 0x00FFFFFF);
        index2 = ((S_818B6F90_0 *)scratch)->unk_04.v2;
        ot2 = (*(u32 * volatile *)((u8 *)scratch + (0x00)));
        ot2[index2] =
            (ot2[index2] & 0xFF000000) |
            ((u32)packet & 0x00FFFFFF);
    }

    return 0;
}
