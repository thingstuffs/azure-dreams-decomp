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

/* Rotate and move a quad, fade its color in and out, then mark it for removal. */
M2C_UNK func_81960CD4(void *quad, S_81960CD4_2 *motion, S_81960CD4_3 *effect) {
    u8 *scratch = (u8 *)0x1F800000;
    u16 rotation[3];
    s16 remaining_count;
    s16 fade_in_ticks;
    s16 fade_out_ticks;
    s32 blue_step;
    u16 center_z;
    u16 effect_count;
    u8 fade_in_blue;
    u8 fade_in_red;
    u8 fade_in_green;
    u8 fade_out_red;
    u8 fade_out_green;
    u8 fade_out_blue;
    u16 update_count;
    u16 vertex_z;

    ((S_81960CD4_0 *)scratch)->unk_70 = ((S_81960CD4_1 *)quad)->unk_10 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_78 = ((S_81960CD4_1 *)quad)->unk_18 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_80 = ((S_81960CD4_1 *)quad)->unk_20 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_88 = ((S_81960CD4_1 *)quad)->unk_28 - motion->unk_00.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_72 = ((S_81960CD4_1 *)quad)->unk_12 - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7A = ((S_81960CD4_1 *)quad)->unk_1A - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_82 = ((S_81960CD4_1 *)quad)->unk_22 - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_8A = ((S_81960CD4_1 *)quad)->unk_2A - motion->unk_04.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_74 = ((S_81960CD4_1 *)quad)->unk_14 - motion->unk_08.at02.v;
    ((S_81960CD4_0 *)scratch)->unk_7C = ((S_81960CD4_1 *)quad)->unk_1C - motion->unk_08.at02.v;
    update_count = D_80027330[0];
    vertex_z = ((S_81960CD4_1 *)quad)->unk_24;
    center_z = motion->unk_08.at02.v;
    D_80027330[0] = (u16)(update_count + 1);
    ((S_81960CD4_0 *)scratch)->unk_84 = vertex_z - center_z;
    ((S_81960CD4_0 *)scratch)->unk_8C = ((S_81960CD4_1 *)quad)->unk_2C - motion->unk_08.at02.v;
    func_800649A0(center_z);
    rotation[0] = effect->unk_16;
    rotation[1] = effect->unk_18;
    rotation[2] = 0;
    ((S_81960CD4_0 *)scratch)->unk_30 = effect->unk_1C;
    ((S_81960CD4_0 *)scratch)->unk_34 = effect->unk_1E;
    ((S_81960CD4_0 *)scratch)->unk_38 = 0x1000;
    ((S_81960CD4_0 *)scratch)->unk_6C = 0;
    ((S_81960CD4_0 *)scratch)->unk_68 = 0;
    ((S_81960CD4_0 *)scratch)->unk_64 = 0;
    func_80065820(rotation, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);
    func_80065320(scratch + 0x70, scratch + 0x98, scratch + 0x94);
    func_80065320(scratch + 0x78, scratch + 0xA0, scratch + 0x94);
    func_80065320(scratch + 0x80, scratch + 0xA8, scratch + 0x94);
    func_80065320(scratch + 0x88, scratch + 0xB0, scratch + 0x94);
    func_80064A40();
    motion->unk_00.at00.v = (s32)(motion->unk_00.at00.v + motion->unk_0C);
    motion->unk_04.at00.v = (s32)(motion->unk_04.at00.v + motion->unk_10);
    motion->unk_08.at00.v = (s32)(motion->unk_08.at00.v + motion->unk_14);
    ((S_81960CD4_1 *)quad)->unk_10 = (u16)(((S_81960CD4_0 *)scratch)->unk_98 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_18 = (u16)(((S_81960CD4_0 *)scratch)->unk_A0 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_20 = (u16)(((S_81960CD4_0 *)scratch)->unk_A8 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_28 = (u16)(((S_81960CD4_0 *)scratch)->unk_B0 + motion->unk_00.at02.v);
    ((S_81960CD4_1 *)quad)->unk_12 = (u16)(((S_81960CD4_0 *)scratch)->unk_9A + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_1A = (u16)(((S_81960CD4_0 *)scratch)->unk_A2 + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_22 = (u16)(((S_81960CD4_0 *)scratch)->unk_AA + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_2A = (u16)(((S_81960CD4_0 *)scratch)->unk_B2 + motion->unk_04.at02.v);
    ((S_81960CD4_1 *)quad)->unk_14 = (u16)(((S_81960CD4_0 *)scratch)->unk_9C + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_1C = (u16)(((S_81960CD4_0 *)scratch)->unk_A4 + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_24 = (u16)(((S_81960CD4_0 *)scratch)->unk_AC + motion->unk_08.at02.v);
    ((S_81960CD4_1 *)quad)->unk_2C = (u16)(((S_81960CD4_0 *)scratch)->unk_B4 + motion->unk_08.at02.v);
    if (((S_81960CD4_1 *)quad)->unk_48.s == 0) {
        fade_in_red = effect->unk_0C;
        effect->unk_0C = (u8)(fade_in_red + ((s32)(0xC0 - fade_in_red) / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_in_green = effect->unk_0D;
        remaining_count = ((S_81960CD4_1 *)quad)->unk_4C;
        fade_in_blue = effect->unk_0E;
        effect->unk_0D = (u8)(fade_in_green + ((s32)(0xC0 - fade_in_green) / remaining_count));
        blue_step = (s32)(0xC0 - fade_in_blue) / (s16)((S_81960CD4_1 *)quad)->unk_4C;
        effect->unk_0E = (u8)(fade_in_blue + blue_step);
        fade_in_ticks = (u16)((S_81960CD4_1 *)quad)->unk_4C - 1;
        ((S_81960CD4_1 *)quad)->unk_4C = fade_in_ticks;
        if ((fade_in_ticks << 0x10) <= 0) {
            motion->unk_0C = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            motion->unk_10 = (s32)(((rand() & 0x1F) - 0x10) << 0x10);
            motion->unk_14 = (s32)(((rand() & 0x3F) - 0x20) << 0x10);
            effect->unk_16 = (u16)((rand() & 0x3FF) - 0x200);
            effect->unk_18 = (u16)((rand() & 0x3FF) - 0x200);
            ((S_81960CD4_1 *)quad)->unk_4C = 0x10;
            ((S_81960CD4_1 *)quad)->unk_48.u = (u16)(((S_81960CD4_1 *)quad)->unk_48.u + 1);
            return func_800269AC();
        }
    } else {
        fade_out_red = effect->unk_0C;
        effect->unk_0C = (u8)(fade_out_red - ((s32)fade_out_red / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_green = effect->unk_0D;
        effect->unk_0D = (u8)(fade_out_green - ((s32)fade_out_green / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_blue = effect->unk_0E;
        effect->unk_0E = (u8)(fade_out_blue - ((s32)fade_out_blue / (s16)((S_81960CD4_1 *)quad)->unk_4C));
        fade_out_ticks = (u16)((S_81960CD4_1 *)quad)->unk_4C - 1;
        ((S_81960CD4_1 *)quad)->unk_4C = fade_out_ticks;
        if ((fade_out_ticks << 0x10) <= 0) {
            remaining_count = *(s16 *)D_800273BC;
            if (remaining_count != 0) {
                effect_count = D_800273BC[0] - 1;
                (*(u16 *)D_800273BC) = effect_count;
                if ((s16)effect_count == 1) {
                    (*(u16 *)D_800273BC) = 0U;
                }
            }
            ((S_81960CD4_1_pre *)quad)[-1].unk_00 = (u16)(((S_81960CD4_1_pre *)quad)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }
}
