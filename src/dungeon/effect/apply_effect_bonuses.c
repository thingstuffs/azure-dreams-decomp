#include "shared/item_ids.h"
#include "shared/actor_property_flags.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "dungeon/effect.h"


typedef struct S_800B3D10_6 {
    u8 unk_00;
} S_800B3D10_6;   /* ((Rec_D_800E3D7C *)arg2)->unk_4C.as_pv in apply_effect_bonuses */


/* cfail-repair: tf7-phase1-cache-v3 */
s32 get_clamped_adjusted_value();                          /* extern */
s32 resolve_alternate_spell_id(); /* Unprototyped: retail call extends the result to this declared width; no shared prototype keeps it */                             /* extern */
extern u8 current_spell_effect_variant;


typedef struct S_800B3D10_1 {
    u8 unk_00;
} S_800B3D10_1;   /* &D_800E3D68 in apply_effect_bonuses */

typedef struct S_800B3D10_2 {
    u8 unk_00;
    u8 unk_01;
} S_800B3D10_2;

typedef struct S_800B3D10_3 {
    u8 unk_00;
    u8 unk_01;
} S_800B3D10_3;

typedef struct S_800B3D10_4 {
    u8 unk_00;
    u8 unk_01;
} S_800B3D10_4;

/* Keep the three effect variants expanded at their original case labels. */
/* May return from the enclosing function and uses the caller locals. */
#define APPLY_TYPE_BONUS(data, flag, kind, bonus_kind) \
data = record->unk_4C; \
record->flags14 = (s32) (record->flags14 | (flag)); \
if (data->unk_01 == ITEM_KIND_WAND) { \
    if (data->unk_00 == (kind)) { \
        record->unk_20 = (s16) ((u16) record->unk_20 \
            + ((s32) (record->unk_20 * ((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00 * 2) / (s32) (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00 \
            + 1))); \
        return; \
    } \
    record->unk_20 = (s16) ((u16) record->unk_20 + ((s32) (record->unk_20 * ((*(u8 *)&current_spell_effect_variant) \
        + ((u8) (*(u8 *)&current_spell_effect_variant) >> 1))) / (s32) ((*(u8 *)&current_spell_effect_variant) + 1))); \
    return; \
} \
bonus_base = record->unk_20 - ((s32) (get_clamped_adjusted_value(record) << 0x10) >> 0xF); \
if (bonus_base < 0) { \
    bonus_base = 0; \
} \
if (((S_800B3D10_6 *)(((ActorRecord *)record)->unk_4C))->unk_00 == (bonus_kind)) { \
    record->unk_20 = (s16) ((u16) record->unk_20 + ((bonus_base * (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00 \
        + (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00 >> 1))) / (s32) (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00 \
        + 1))); \
} else { \
    record->unk_20 = (s16) ((u16) record->unk_20 \
        + ((bonus_base * ((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00) / (s32) (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00 \
        + 1))); \
} \
return;

/* Apply effect flags and value bonuses based on the effect and attached record data. */
void apply_effect_bonuses(s16 effect_id, ActorRecord *unused_arg, ActorRecord *record) {
    s32 effect_offset;
    s32 effect_index;
    s16 unused_value;
    s32 bonus_base;
    s32 updated_flags;
    S_800B3D10_2 *type6_data;
    S_800B3D10_3 *type7_data;
    S_800B3D10_4 *type8_data;

    effect_offset = resolve_alternate_spell_id(effect_id) - 1;
    effect_index = (s16) effect_offset;
    switch (effect_index) {
    case 0:
    {
        s32 value_bonus =
            (s32) (record->unk_20 * ((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00) / (s32) (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00
            + 1);
        s32 flags = record->flags14 | ACTOR_ELEMENT_FIRE;
        record->flags14 = flags;
        record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
        return;
    }
    case 1:
    {
        s32 value_bonus =
            (s32) (record->unk_20 * ((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00) / (s32) (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00
            + 1);
        s32 flags = record->flags14 | ACTOR_ELEMENT_WATER;
        record->flags14 = flags;
        record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
        return;
    }
    case 2:
    {
        s32 value_bonus =
            (s32) (record->unk_20 * ((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00) / (s32) (((S_800B3D10_1 *)(&current_spell_effect_variant))->unk_00
            + 1);
        s32 flags = record->flags14 | ACTOR_ELEMENT_WIND;
        record->flags14 = flags;
        record->unk_20 = (s16) ((u16) record->unk_20 + value_bonus);
        return;
    }
    case 6:
        APPLY_TYPE_BONUS(type6_data, ACTOR_ELEMENT_FIRE, ITEM_SCARLET_WAND, 5);
    case 7:
        APPLY_TYPE_BONUS(type7_data, ACTOR_ELEMENT_WATER, ITEM_STREAM_WAND, 6);
    case 8:
        APPLY_TYPE_BONUS(type8_data, ACTOR_ELEMENT_WIND, ITEM_GULF_WAND, 7);
    case 12:
    case 39:
    case 42:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_FIRE;
        return;
    case 13:
    case 40:
    case 43:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_WATER;
        return;
    case 15:
    case 18:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_FIRE;
        return;
    case 16:
    case 19:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_WATER;
        return;
    case 21:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_FIRE;
        return;
    case 22:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_WATER;
        return;
    case 30:
    case 33:
    case 36:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_FIRE;
        return;
    case 31:
    case 34:
    case 37:
        record->flags14 = record->flags14 | ACTOR_ELEMENT_WATER;
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
        updated_flags = record->flags14 | ACTOR_ELEMENT_WIND;
        record->flags14 = updated_flags;
        return;
    case 48:
    default:
        return;
    }
}

#undef APPLY_TYPE_BONUS
