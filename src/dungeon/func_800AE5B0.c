#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B3D10_5 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_800B3D10_5;   /* arg2 in func_800B3D10 */

typedef struct S_800B3D10_6 {
    u8 unk_00;
} S_800B3D10_6;   /* ((S_800B3D10_5 *)arg2)->unk_4C in func_800B3D10 */




/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089200[];
s32 func_800981F8();                          /* extern */
s32 func_800A9400();                             /* extern */
extern u8 D_800E3D68;

typedef struct S_800B3D10_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
    u8 pad_22[0x2A];
    void * unk_4C;
} S_800B3D10_0;   /* arg2 in func_800B3D10 */

typedef struct S_800B3D10_1 {
    u8 unk_00;
} S_800B3D10_1;   /* &D_800E3D68 in func_800B3D10 */

typedef struct S_800B3D10_2 {
    u8 unk_00;
    u8 unk_01;
} S_800B3D10_2;   /* temp_a0 in func_800B3D10 */

typedef struct S_800B3D10_3 {
    u8 unk_00;
    u8 unk_01;
} S_800B3D10_3;   /* temp_a0_2 in func_800B3D10 */

typedef struct S_800B3D10_4 {
    u8 unk_00;
    u8 unk_01;
} S_800B3D10_4;   /* temp_a0_3 in func_800B3D10 */

void func_800B3D10(s16 arg0, s32 arg1, S_800B3D10_0 *arg2) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c30, &&jt_c31, &&jt_c32, &&jt_c33, &&jt_c34, &&jt_c35, &&jt_c36, &&jt_c37, &&jt_c38, &&jt_c39, &&jt_c40, &&jt_c41, &&jt_c42, &&jt_c43, &&jt_c44 };
    s32 temp_v0;
    s32 temp_v1;
    s16 var_v0_2;
    s32 var_a0;
    s32 var_v0_4;
    S_800B3D10_2 *temp_a0;
    S_800B3D10_3 *temp_a0_2;
    S_800B3D10_4 *temp_a0_3;

    temp_v0 = func_800A9400(arg0) - 1;
    temp_v1 = (s16) temp_v0;
    if ((u32) (s32) temp_v1 < 0x31U) {
        (void)jt_keep; goto *D_80089200[(u32) (s32) temp_v1];
    }
    goto block_43;
jt_c0:
{
    s32 result = (s32) (arg2->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1);
    s32 flags = arg2->unk_14 | 1;
    arg2->unk_14 = flags;
    arg2->unk_20 = (s16) ((u16) arg2->unk_20 + result);
    return;
}
jt_c1:
{
    s32 result = (s32) (arg2->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1);
    s32 flags = arg2->unk_14 | 2;
    arg2->unk_14 = flags;
    arg2->unk_20 = (s16) ((u16) arg2->unk_20 + result);
    return;
}
jt_c2:
{
    s32 result = (s32) (arg2->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1);
    s32 flags = arg2->unk_14 | 4;
    arg2->unk_14 = flags;
    arg2->unk_20 = (s16) ((u16) arg2->unk_20 + result);
    return;
}
jt_c6:
    temp_a0 = arg2->unk_4C;
    arg2->unk_14 = (s32) (arg2->unk_14 | 1);
    if (temp_a0->unk_01 == 0x10) {
        if (temp_a0->unk_00 == 6) {
            arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((s32) (arg2->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
            return;
        }
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((s32) (arg2->unk_20 * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    var_a0 = arg2->unk_20 - ((s32) (func_800981F8(arg2) << 0x10) >> 0xF);
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (((S_800B3D10_6 *)(((S_800B3D10_5 *)arg2)->unk_4C))->unk_00 == 5) {
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((var_a0 * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    } else {
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((var_a0 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    }
    return;
jt_c7:
    temp_a0_2 = arg2->unk_4C;
    arg2->unk_14 = (s32) (arg2->unk_14 | 2);
    if (temp_a0_2->unk_01 == 0x10) {
        if (temp_a0_2->unk_00 == 7) {
            arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((s32) (arg2->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
            return;
        }
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((s32) (arg2->unk_20 * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    var_a0 = arg2->unk_20 - ((s32) (func_800981F8(arg2) << 0x10) >> 0xF);
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (((S_800B3D10_6 *)(((S_800B3D10_5 *)arg2)->unk_4C))->unk_00 == 6) {
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((var_a0 * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    } else {
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((var_a0 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    }
    return;
jt_c8:
    temp_a0_3 = arg2->unk_4C;
    arg2->unk_14 = (s32) (arg2->unk_14 | 4);
    if (temp_a0_3->unk_01 == 0x10) {
        if (temp_a0_3->unk_00 == 8) {
            arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((s32) (arg2->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
            return;
        }
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((s32) (arg2->unk_20 * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    var_a0 = arg2->unk_20 - ((s32) (func_800981F8(arg2) << 0x10) >> 0xF);
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    if (((S_800B3D10_6 *)(((S_800B3D10_5 *)arg2)->unk_4C))->unk_00 == 7) {
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((var_a0 * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    } else {
        arg2->unk_20 = (s16) ((u16) arg2->unk_20 + ((var_a0 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    }
    return;
jt_c12:
jt_c39:
jt_c42:
    arg2->unk_14 = arg2->unk_14 | 1;
    return;
jt_c13:
jt_c40:
jt_c43:
    arg2->unk_14 = arg2->unk_14 | 2;
    return;
jt_c15:
jt_c18:
    arg2->unk_14 = arg2->unk_14 | 1;
    return;
jt_c16:
jt_c19:
    arg2->unk_14 = arg2->unk_14 | 2;
    return;
jt_c21:
    arg2->unk_14 = arg2->unk_14 | 1;
    return;
jt_c22:
    arg2->unk_14 = arg2->unk_14 | 2;
    return;
jt_c30:
jt_c33:
jt_c36:
    arg2->unk_14 = arg2->unk_14 | 1;
    return;
jt_c31:
jt_c34:
jt_c37:
    arg2->unk_14 = arg2->unk_14 | 2;
    return;
jt_c14:
jt_c17:
jt_c20:
jt_c23:
jt_c32:
jt_c35:
jt_c38:
jt_c41:
jt_c44:
    var_v0_4 = arg2->unk_14 | 4;
block_42:
    arg2->unk_14 = var_v0_4;
block_43:
    return;
}
