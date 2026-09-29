#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


typedef struct S_800B3D10_6 {
    u8 unk_00;
} S_800B3D10_6;   /* ((Rec_D_800E3D7C *)arg2)->unk_4C.as_pv in func_800B3D10 */


/* cfail-repair: tf7-phase1-cache-v3 */
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
void func_800B3D10(s16 effect_id, s32 unused_arg, EntityRec *record) {
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
    switch (effect_index) {
    case 0:
    {
        s32 value_bonus =
            (s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
            + 1);
        s32 flags = record->flags14 | 1;
        record->flags14 = flags;
        record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
        return;
    }
    case 1:
    {
        s32 value_bonus =
            (s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
            + 1);
        s32 flags = record->flags14 | 2;
        record->flags14 = flags;
        record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
        return;
    }
    case 2:
    {
        s32 value_bonus =
            (s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
            + 1);
        s32 flags = record->flags14 | 4;
        record->flags14 = flags;
        record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
        return;
    }
    case 6:
        type6_data = record->unk_4C;
        record->flags14 = (s32) (record->flags14 | 1);
        if (type6_data->unk_01 == 0x10) {
            if (type6_data->unk_00 == 6) {
                record->unk_20 = (s16) ((u16) record->unk_20
                    + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                    + 1)));
                return;
            }
            record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&D_800E3D68)
                + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
            return;
        }
        bonus_base = record->unk_20 - ((s32) (func_800981F8(record) << 0x10) >> 0xF);
        if (bonus_base < 0) {
            bonus_base = 0;
        }
        if (((S_800B3D10_6 *)(((EntityRec *)record)->unk_4C))->unk_00 == 5) {
            record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + 1)));
        } else {
            record->unk_20 = (s16) ((u16) record->unk_20
                + ((bonus_base * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + 1)));
        }
        return;
    case 7:
        type7_data = record->unk_4C;
        record->flags14 = (s32) (record->flags14 | 2);
        if (type7_data->unk_01 == 0x10) {
            if (type7_data->unk_00 == 7) {
                record->unk_20 = (s16) ((u16) record->unk_20
                    + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                    + 1)));
                return;
            }
            record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&D_800E3D68)
                + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
            return;
        }
        bonus_base = record->unk_20 - ((s32) (func_800981F8(record) << 0x10) >> 0xF);
        if (bonus_base < 0) {
            bonus_base = 0;
        }
        if (((S_800B3D10_6 *)(((EntityRec *)record)->unk_4C))->unk_00 == 6) {
            record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + 1)));
        } else {
            record->unk_20 = (s16) ((u16) record->unk_20
                + ((bonus_base * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + 1)));
        }
        return;
    case 8:
        type8_data = record->unk_4C;
        record->flags14 = (s32) (record->flags14 | 4);
        if (type8_data->unk_01 == 0x10) {
            if (type8_data->unk_00 == 8) {
                record->unk_20 = (s16) ((u16) record->unk_20
                    + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                    + 1)));
                return;
            }
            record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&D_800E3D68)
                + ((u8) (*(u8 *)&D_800E3D68) >> 1))) / (s32) ((*(u8 *)&D_800E3D68) + 1)));
            return;
        }
        bonus_base = record->unk_20 - ((s32) (func_800981F8(record) << 0x10) >> 0xF);
        if (bonus_base < 0) {
            bonus_base = 0;
        }
        if (((S_800B3D10_6 *)(((EntityRec *)record)->unk_4C))->unk_00 == 7) {
            record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + (((S_800B3D10_1 *)(&D_800E3D68))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + 1)));
        } else {
            record->unk_20 = (s16) ((u16) record->unk_20
                + ((bonus_base * ((S_800B3D10_1 *)(&D_800E3D68))->unk_00) / (s32) (((S_800B3D10_1 *)(&D_800E3D68))->unk_00
                + 1)));
        }
        return;
    case 12:
    case 39:
    case 42:
        record->flags14 = record->flags14 | 1;
        return;
    case 13:
    case 40:
    case 43:
        record->flags14 = record->flags14 | 2;
        return;
    case 15:
    case 18:
        record->flags14 = record->flags14 | 1;
        return;
    case 16:
    case 19:
        record->flags14 = record->flags14 | 2;
        return;
    case 21:
        record->flags14 = record->flags14 | 1;
        return;
    case 22:
        record->flags14 = record->flags14 | 2;
        return;
    case 30:
    case 33:
    case 36:
        record->flags14 = record->flags14 | 1;
        return;
    case 31:
    case 34:
    case 37:
        record->flags14 = record->flags14 | 2;
        return;
    case 14:
    case 17:
    case 20:
    case 23:
    case 32:
    case 35:
    case 38:
    case 41:
    case 44:
        updated_flags = record->flags14 | 4;
        record->flags14 = updated_flags;
        return;
    case 48:
    default:
        return;
    }
}
