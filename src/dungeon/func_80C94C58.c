#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172458_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
    s16 unk_A4;
    s16 unk_A6;
    u16 unk_A8;
} S_80172458_0;   /* arg0 in func_80172458 */





M2C_UNK func_800419EC();            /* extern */
M2C_UNK func_80047784();         /* extern */
s32 func_800644B8();                             /* extern */
s16 func_800A0818();       /* extern */
M2C_UNK func_800A2B04();              /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800A9A04();                      /* extern */
M2C_UNK func_800AD594();             /* extern */
s32 func_800AD9B4();                  /* extern */
M2C_UNK func_800B66C8();                      /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern u8 D_8017102C[];
extern u8 D_801752CC[];
extern u8 D_801752D4[];

void func_80172458(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK sp18;
    s32 temp_a0;
    s16 temp_v0;
    s16 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v1;
    s16 *global_base;
    u8 *map_base;
    register s32 temp_result ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 mask_a0;
    register s32 temp_diff ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 temp_v0_2;
    s32 temp_v1;

    temp_v1 = ((S_80172458_0 *)arg0)->unk_9B;
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 >= 2) {
        goto state_ge2;
    }
    if (temp_v1 == 0) {
        goto state_zero;
    }
    goto block_36;
state_ge2:
    if (temp_v1 == 2) {
        goto block_34;
    }
    goto block_36;
state_zero:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_801752CC;
        func_80047784(arg2, D_801752CC[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        ((S_80172458_0 *)arg0)->unk_98 = (u16) (((S_80172458_0 *)arg0)->unk_98 | 8);
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0xF7FFFFFF);
        ((S_80172458_0 *)arg0)->unk_9E = 5;
        ((S_80172458_0 *)arg0)->unk_A0 = 0;
        ((S_80172458_0 *)arg0)->unk_9B = (u8) (((S_80172458_0 *)arg0)->unk_9B + 1);
        ((S_80172458_0 *)arg0)->unk_A6 = func_800BCB04((((Rec_D_80082E80 *)arg2)->unk_24 << 6) | 0x20, (((Rec_D_80082E80 *)arg2)->unk_25 << 6) | 0x20, (s16) (((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 - 0x20));
        ((S_80172458_0 *)arg0)->unk_A8 = (u16) ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v;
        goto block_10;
    }
    goto block_36;
block_10:
    temp_a0 = ((S_80172458_0 *)arg0)->unk_9E;
    ((S_80172458_0 *)arg0)->unk_90 = (s32) (((S_80172458_0 *)arg0)->unk_90 - ((S_80172458_0 *)arg0)->unk_A0);
    if (temp_a0 != 0) {
        temp_result = ((Rec_D_80082E80 *)arg2)->unk_24;
        temp_diff = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
        temp_result <<= 6;
        temp_diff -= 0x20;
        temp_result = ((temp_result - temp_diff) << 0x10) / temp_a0;
        temp_diff = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = temp_result;
        temp_result = ((Rec_D_80082E80 *)arg2)->unk_25;
        temp_diff -= 0x20;
        temp_result <<= 6;
        temp_result -= temp_diff;
        temp_diff = ((S_80172458_0 *)arg0)->unk_9E;
        temp_result = (temp_result << 0x10) / temp_diff;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = temp_result;
        if (((S_80172458_0 *)arg0)->unk_A4 == 3) {
            ((S_80172458_0 *)arg0)->unk_A0 = (s32) ((0 - func_800644B8(((S_80172458_0 *)arg0)->unk_9E * 0x155)) << 9);
            ((S_80172458_0 *)arg0)->unk_90 += ((S_80172458_0 *)arg0)->unk_A0;
            goto block_32;
        }
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        temp_v1_2 = ((S_80172458_0 *)arg0)->unk_9E;
        if (temp_v1_2 == 4) {
            goto case_4;
        }
        if (temp_v1_2 >= 5) {
            goto case_ge5;
        }
        if (temp_v1_2 == 3) {
            goto case_3;
        }
        ((S_80172458_0 *)arg0)->unk_90 = 0;
        goto block_32;
case_ge5:
        if (temp_v1_2 == 5) {
            goto case_5;
        }
        mask_a0 = 0xF7FF0000;
        if (temp_v1_2 != 6) {
            goto case_default;
        }
        temp_diff = (((S_80172458_0 *)arg0)->unk_A6 - (s16) ((S_80172458_0 *)arg0)->unk_A8) << 0x10;
        temp_result = (s32) (0xFFFE0000 - temp_diff);
        goto mask_flags;
case_5:
        temp_result = (s32) (0 - ((((S_80172458_0 *)arg0)->unk_A6 - (s16) ((S_80172458_0 *)arg0)->unk_A8) << 0x10));
        mask_a0 = 0xF7FF0000;
mask_flags:
        ((S_80172458_0 *)arg0)->unk_90 = temp_result;
        mask_a0 |= 0xFFFF;
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & mask_a0);
        goto block_32;
case_4:
        var_v1 = (((S_80172458_0 *)arg0)->unk_A6 - (s16) ((S_80172458_0 *)arg0)->unk_A8) * 3;
        if (var_v1 < 0) {
            var_v1 += 3;
        }
        ((S_80172458_0 *)arg0)->unk_90 = (s32) (0 - ((var_v1 >> 2) << 0x10));
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0xF7FFFFFF);
        goto block_32;
case_3:
        ((S_80172458_0 *)arg0)->unk_90 = (s32) (0 - ((((((S_80172458_0 *)arg0)->unk_A6 - (s16) ((S_80172458_0 *)arg0)->unk_A8) * 2) / 5) << 0x10));
        goto block_32;
case_default:
        ((S_80172458_0 *)arg0)->unk_90 = 0;
    }
block_32:
    temp_v0 = (u16) ((S_80172458_0 *)arg0)->unk_9E - 1;
    ((S_80172458_0 *)arg0)->unk_9E = temp_v0;
    if (temp_v0 < 0) {
        ((S_80172458_0 *)arg0)->unk_90 = 0;
        ((S_80172458_0 *)arg0)->unk_98 = (u16) (((S_80172458_0 *)arg0)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 | 0x08000000);
        ((S_80172458_0 *)arg0)->unk_9B = (u8) (((S_80172458_0 *)arg0)->unk_9B + 1);
    }
block_34:
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x08000000) {
        ((S_80172458_0 *)arg0)->unk_98 = (u16) (((S_80172458_0 *)arg0)->unk_98 & 0xFFF7);
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_801752D4;
        func_80047784(arg2, D_801752D4[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
        func_800419EC(4, 8);
        func_800B66C8(arg1);
        ((S_80172458_0 *)arg0)->unk_9B = 3U;
    }
block_36:
    temp_v0_2 = ((S_80172458_0 *)arg0)->unk_96 - 1;
    ((S_80172458_0 *)arg0)->unk_96 = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        global_base = (s16 *)&D_80083460;
        if (global_base[4] != 0) {
            global_base[4] = (s16) ((u16) global_base[4] - 1);
        }
        temp_v1_3 = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
        if (temp_v1_3 & 0x2000) {
            temp_v0_2 = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v;
            if (temp_v0_2 & 0x8000) {
                ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = temp_v0_2 & 0x7FFF;
            }
            goto block_46;
        }
        if (temp_v1_3 & 0x410) {
            goto block_46;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_46;
        }
        map_base = (u8 *)&D_80082E80;
        ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25, map_base[0x24], map_base[0x25], &sp18);
block_46:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            ((S_80172458_0 *)arg0)->unk_8C = D_8017102C;
            func_800A9A04(arg3);
        }
    }
}
