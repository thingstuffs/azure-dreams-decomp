#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800B3D10_6 {
    u8 unk_00;
} S_800B3D10_6;   /* ((Rec_D_800E3D7C *)arg2)->unk_4C.as_pv in func_800B3D10 */




/* cfail-repair: tf7-phase1-cache-v3 */
extern void *D_80089200[];
s32 func_800981F8();                          /* extern */
s32 func_800A9400();                             /* extern */
extern u8 D_800E3D68;


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

/* Apply effect flags and value bonuses based on the effect and attached record data. */
void func_800B3D10(s16 effect_id, s32 unused_arg, Rec_D_800E3D7C *record) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c6, &&jt_c7, &&jt_c8, &&jt_c12, &&jt_c13, &&jt_c14, &&jt_c15, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19, &&jt_c20, &&jt_c21, &&jt_c22, &&jt_c23, &&jt_c30, &&jt_c31, &&jt_c32, &&jt_c33, &&jt_c34, &&jt_c35, &&jt_c36, &&jt_c37, &&jt_c38, &&jt_c39, &&jt_c40, &&jt_c41, &&jt_c42, &&jt_c43, &&jt_c44 };
    s32 effect_offset;
    s32 effect_index;
    s16 unused_value;
    s32 bonus_base;
    s32 updated_flags;
    S_800B3D10_2 *type6_data;
    S_800B3D10_3 *type7_data;
    S_800B3D10_4 *type8_data;

    effect_offset = func_800A9400(effect_id) - 1;
    effect_index = (s16) effect_offset;
    if ((u32) (s32) effect_index < 0x31U) {
        (void)jt_keep; goto *D_80089200[(u32) (s32) effect_index];
    }
    goto block_43;
jt_c0:
{
    s32 value_bonus = (s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1);
    s32 flags = record->unk_14.as_s32 | 1;
    record->unk_14.as_s32 = flags;
    record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
    return;
}
jt_c1:
{
    s32 value_bonus = (s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1);
    s32 flags = record->unk_14.as_s32 | 2;
    record->unk_14.as_s32 = flags;
    record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
    return;
}
jt_c2:
{
    s32 value_bonus = (s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1);
    s32 flags = record->unk_14.as_s32 | 4;
    record->unk_14.as_s32 = flags;
    record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
    return;
}
jt_c6:
    type6_data = record->unk_4C.as_pv;
    record->unk_14.as_s32 = (s32) (record->unk_14.as_s32 | 1);
    if (type6_data->unk_01 == 0x10) {
        if (type6_data->unk_00 == 6) {
            record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
            return;
        }
        record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    bonus_base = record->unk_20 - ((s32) (func_800981F8(record) << 0x10) >> 0xF);
    if (bonus_base < 0) {
        bonus_base = 0;
    }
    if (((S_800B3D10_6 *)(((Rec_D_800E3D7C *)record)->unk_4C.as_pv))->unk_00 == 5) {
        record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    } else {
        record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    }
    return;
jt_c7:
    type7_data = record->unk_4C.as_pv;
    record->unk_14.as_s32 = (s32) (record->unk_14.as_s32 | 2);
    if (type7_data->unk_01 == 0x10) {
        if (type7_data->unk_00 == 7) {
            record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
            return;
        }
        record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    bonus_base = record->unk_20 - ((s32) (func_800981F8(record) << 0x10) >> 0xF);
    if (bonus_base < 0) {
        bonus_base = 0;
    }
    if (((S_800B3D10_6 *)(((Rec_D_800E3D7C *)record)->unk_4C.as_pv))->unk_00 == 6) {
        record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    } else {
        record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    }
    return;
jt_c8:
    type8_data = record->unk_4C.as_pv;
    record->unk_14.as_s32 = (s32) (record->unk_14.as_s32 | 4);
    if (type8_data->unk_01 == 0x10) {
        if (type8_data->unk_00 == 8) {
            record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
            return;
        }
        record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&D_800E3D68) + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
        return;
    }
    bonus_base = record->unk_20 - ((s32) (func_800981F8(record) << 0x10) >> 0xF);
    if (bonus_base < 0) {
        bonus_base = 0;
    }
    if (((S_800B3D10_6 *)(((Rec_D_800E3D7C *)record)->unk_4C.as_pv))->unk_00 == 7) {
        record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    } else {
        record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 + 1)));
    }
    return;
jt_c12:
jt_c39:
jt_c42:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 1;
    return;
jt_c13:
jt_c40:
jt_c43:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 2;
    return;
jt_c15:
jt_c18:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 1;
    return;
jt_c16:
jt_c19:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 2;
    return;
jt_c21:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 1;
    return;
jt_c22:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 2;
    return;
jt_c30:
jt_c33:
jt_c36:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 1;
    return;
jt_c31:
jt_c34:
jt_c37:
    record->unk_14.as_s32 = record->unk_14.as_s32 | 2;
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
    updated_flags = record->unk_14.as_s32 | 4;
block_42:
    record->unk_14.as_s32 = updated_flags;
block_43:
    return;
}
