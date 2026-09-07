#include "common.h"
#include "m2c_compat.h"

typedef struct S_81960CD4_0 {
    u8 pad_00[0x30];
    u32 unk_30;
    u32 unk_34;
    u32 unk_38;
    u8 pad_3C[0x28];
    u32 unk_64;
    u32 unk_68;
    u32 unk_6C;
    u16 unk_70;
    u16 unk_72;
    u16 unk_74;
    u8 pad_76[0x2];
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u8 pad_86[0x2];
    u16 unk_88;
    u16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0xA];
    u16 unk_98;
    u16 unk_9A;
    u16 unk_9C;
    u8 pad_9E[0x2];
    u16 unk_A0;
    u16 unk_A2;
    u16 unk_A4;
    u8 pad_A6[0x2];
    u16 unk_A8;
    u16 unk_AA;
    u16 unk_AC;
    u8 pad_AE[0x2];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
} S_81960CD4_0;   /* scratch in func_81960CD4 */

typedef struct S_81960CD4_1_pre {
    u16 unk_00;
} S_81960CD4_1_pre;   /* the 0x2 bytes before arg0 in func_81960CD4, addressed as arg0[-1] */

typedef struct S_81960CD4_1 {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x1A];
    union { s16 s; u16 u; } unk_48;   /* accessed as both */
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_81960CD4_1;   /* arg0 in func_81960CD4 */

typedef struct S_81960CD4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_81960CD4_2;   /* arg1 in func_81960CD4 */

typedef struct S_81960CD4_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x7];
    u16 unk_16;
    u16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
    u16 unk_1E;
} S_81960CD4_3;   /* arg2 in func_81960CD4 */

extern u16 D_80027330[5];
extern s32 D_800814A0[3];
M2C_UNK func_800269AC() __attribute__((noreturn));
M2C_UNK func_800649A0();
M2C_UNK func_80064A40();
M2C_UNK func_80064CF0();
M2C_UNK func_80064D80();
M2C_UNK func_80065320();
M2C_UNK func_80065820();
s32 rand();
extern u16 D_800273BC[5];

M2C_UNK func_81960CD4(void *arg0, S_81960CD4_2 *arg1, S_81960CD4_3 *arg2) {
    u8 *scratch = (u8 *)0x1F800000;
    u16 sp10[3];
    s16 temp_a1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_lo;
    u16 temp_a0;
    u16 temp_v0_4;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u16 counter;
    u16 temp_v1_6;

    ((S_81960CD4_0 *)scratch)->unk_70 = ((S_81960CD4_1 *)arg0)->unk_10 - arg1->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_78 = ((S_81960CD4_1 *)arg0)->unk_18 - arg1->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_80 = ((S_81960CD4_1 *)arg0)->unk_20 - arg1->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_88 = ((S_81960CD4_1 *)arg0)->unk_28 - arg1->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_72 = ((S_81960CD4_1 *)arg0)->unk_12 - arg1->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7A = ((S_81960CD4_1 *)arg0)->unk_1A - arg1->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_82 = ((S_81960CD4_1 *)arg0)->unk_22 - arg1->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_8A = ((S_81960CD4_1 *)arg0)->unk_2A - arg1->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_74 = ((S_81960CD4_1 *)arg0)->unk_14 - arg1->unk_08.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7C = ((S_81960CD4_1 *)arg0)->unk_1C - arg1->unk_08.at02.v;
    counter = D_80027330[0];
    temp_v1_6 = ((S_81960CD4_1 *)arg0)->unk_24;
    temp_a0 = arg1->unk_08.at02.v;
    D_80027330[0] = (u16)(counter + 1);
    ((S_81960CD4_0 *)scratch)->unk_84 = temp_v1_6 - temp_a0;
    ((S_81960CD4_0 *)scratch)->unk_8C = ((S_81960CD4_1 *)arg0)->unk_2C - arg1->unk_08.at02.v;
    func_800649A0(temp_a0);
    sp10[0] = arg2->unk_16;
    sp10[1] = arg2->unk_18;
    sp10[2] = 0;
    ((S_81960CD4_0 *)scratch)->unk_30 = arg2->unk_1C;
    ((S_81960CD4_0 *)scratch)->unk_34 = arg2->unk_1E;
    ((S_81960CD4_0 *)scratch)->unk_38 = 0x1000;
    ((S_81960CD4_0 *)scratch)->unk_6C = 0;
    ((S_81960CD4_0 *)scratch)->unk_68 = 0;
    ((S_81960CD4_0 *)scratch)->unk_64 = 0;
    func_80065820(sp10, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);
    func_80065320(scratch + 0x70, scratch + 0x98, scratch + 0x94);
    func_80065320(scratch + 0x78, scratch + 0xA0, scratch + 0x94);
    func_80065320(scratch + 0x80, scratch + 0xA8, scratch + 0x94);
    func_80065320(scratch + 0x88, scratch + 0xB0, scratch + 0x94);
    func_80064A40();
    arg1->unk_00.at00.v = (s32)(arg1->unk_00.at00.v + arg1->unk_0C);
    arg1->unk_04.at00.v = (s32)(arg1->unk_04.at00.v + arg1->unk_10);
    arg1->unk_08.at00.v = (s32)(arg1->unk_08.at00.v + arg1->unk_14);
    ((S_81960CD4_1 *)arg0)->unk_10 = (u16)(((S_81960CD4_0 *)scratch)->unk_98 + arg1->unk_00.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_18 = (u16)(((S_81960CD4_0 *)scratch)->unk_A0 + arg1->unk_00.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_20 = (u16)(((S_81960CD4_0 *)scratch)->unk_A8 + arg1->unk_00.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_28 = (u16)(((S_81960CD4_0 *)scratch)->unk_B0 + arg1->unk_00.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_12 = (u16)(((S_81960CD4_0 *)scratch)->unk_9A + arg1->unk_04.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_1A = (u16)(((S_81960CD4_0 *)scratch)->unk_A2 + arg1->unk_04.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_22 = (u16)(((S_81960CD4_0 *)scratch)->unk_AA + arg1->unk_04.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_2A = (u16)(((S_81960CD4_0 *)scratch)->unk_B2 + arg1->unk_04.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_14 = (u16)(((S_81960CD4_0 *)scratch)->unk_9C + arg1->unk_08.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_1C = (u16)(((S_81960CD4_0 *)scratch)->unk_A4 + arg1->unk_08.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_24 = (u16)(((S_81960CD4_0 *)scratch)->unk_AC + arg1->unk_08.at02.v);
    ((S_81960CD4_1 *)arg0)->unk_2C = (u16)(((S_81960CD4_0 *)scratch)->unk_B4 + arg1->unk_08.at02.v);
    if (((S_81960CD4_1 *)arg0)->unk_48.s == 0) {
        temp_v1 = arg2->unk_0C;
        arg2->unk_0C = (u8)(temp_v1 + ((s32)(0xC0 - temp_v1) / (s16)((S_81960CD4_1 *)arg0)->unk_4C));
        temp_v1_2 = arg2->unk_0D;
        temp_a1 = ((S_81960CD4_1 *)arg0)->unk_4C;
        temp_v0 = arg2->unk_0E;
        arg2->unk_0D = (u8)(temp_v1_2 + ((s32)(0xC0 - temp_v1_2) / temp_a1));
        temp_lo = (s32)(0xC0 - temp_v0) / (s16)((S_81960CD4_1 *)arg0)->unk_4C;
        arg2->unk_0E = (u8)(temp_v0 + temp_lo);
        temp_v0_2 = (u16)((S_81960CD4_1 *)arg0)->unk_4C - 1;
        ((S_81960CD4_1 *)arg0)->unk_4C = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            arg1->unk_0C = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            arg1->unk_10 = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            arg1->unk_14 = (s32)(((rand() & 0x3F) - 0x20) << 0x10);
            arg2->unk_16 = (u16)((rand() & 0x3FF) - 0x200);
            arg2->unk_18 = (u16)((rand() & 0x3FF) - 0x200);
            ((S_81960CD4_1 *)arg0)->unk_4C = 0x10;
            ((S_81960CD4_1 *)arg0)->unk_48.u = (u16)(((S_81960CD4_1 *)arg0)->unk_48.u + 1);
            return func_800269AC();
        }
    } else {
        temp_v1_3 = arg2->unk_0C;
        arg2->unk_0C = (u8)(temp_v1_3 - ((s32)temp_v1_3 / (s16)((S_81960CD4_1 *)arg0)->unk_4C));
        temp_v1_4 = arg2->unk_0D;
        arg2->unk_0D = (u8)(temp_v1_4 - ((s32)temp_v1_4 / (s16)((S_81960CD4_1 *)arg0)->unk_4C));
        temp_v1_5 = arg2->unk_0E;
        arg2->unk_0E = (u8)(temp_v1_5 - ((s32)temp_v1_5 / (s16)((S_81960CD4_1 *)arg0)->unk_4C));
        temp_v0_3 = (u16)((S_81960CD4_1 *)arg0)->unk_4C - 1;
        ((S_81960CD4_1 *)arg0)->unk_4C = temp_v0_3;
        if ((temp_v0_3 << 0x10) <= 0) {
            temp_a1 = *(s16 *)D_800273BC;
            if (temp_a1 != 0) {
                temp_v0_4 = D_800273BC[0] - 1;
                (*(u16 *)D_800273BC) = temp_v0_4;
                if ((s16)temp_v0_4 == 1) {
                    (*(u16 *)D_800273BC) = 0U;
                }
            }
            ((S_81960CD4_1_pre *)arg0)[-1].unk_00 = (u16)(((S_81960CD4_1_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }
}
