#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect.h"
#include "engine/cd.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/actor/effect.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_80E3C98C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80E3C98C_1;   /* arg2 in spawn_manoeva_from_record */

typedef struct S_80E3C98C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80E3C98C_2_pre;

typedef struct S_80E3C98C_2 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
} S_80E3C98C_2;

typedef struct S_80E3C98C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80E3C98C_3_pre;

typedef struct S_80E3C98C_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80E3C98C_3;

typedef struct S_80E3C98C_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80E3C98C_4;

typedef struct S_80E3C98C_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
    u8 pad_B0[0x34];
    void * unk_E4;
} S_80E3C98C_5;

typedef struct S_80E3C98C_6 {
    u8 pad_00[0x12];
    s16 unk_12;
} S_80E3C98C_6;

typedef struct S_80E3C98C_7 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80E3C98C_7;


extern s32 func_80042640();
extern s32 copy_entity_record();
extern s32 set_code_for_entity_mode();
extern void *(*load_monster_resource_data())(s32, u8, u8, s16);
extern void *find_or_retain_sprite_resource_slot();
extern s8 entity_spawn_variant_code;

/* Create an entity from spawn data and update its tracked reference. */
void *spawn_manoeva_from_record(void *unused0, void *unused1, S_80E3C98C_1 *position, Rec_D_80082E80 *spawn_data) {
    s32 spawn_mode;
    s32 source_ref;
    u8 *table_base;
    void *(*create_entity)(s32, u8, u8, s16);
    s32 table_offset;
    S_80E3C98C_5 *table_entry;
    void *previous_entity;
    void *source_entity;
    void *entity;
    S_80E3C98C_4 *type_data;
    void *result;

    source_ref = spawn_data->unk_60.as_s32;
    if (source_ref > 0) {
        entity = create_mode_configured_object(((u32)spawn_data->unk_1C.at00_u32.v >> 0xD) & 1,
                               position->unk_24, position->unk_25,
                               spawn_data->unk_88.as_s16,
                               get_item_category_value(((s32)(((u16)spawn_data->unk_60.as_s32 - 1) << 0x10) >> 0xE)
                                   + ((u8 *)dungeon_ground_items)));
        if (entity != NULL) {
            ((S_80E3C98C_2 *)entity)->unk_14 = 0;
            ((S_80E3C98C_2 *)entity)->unk_1C = 0;
            copy_entity_record(entity, spawn_data);
            ((S_80E3C98C_2 *)entity)->unk_14 |= 0x20000000;
            ((S_80E3C98C_2 *)entity)->unk_1C =
                (((S_80E3C98C_2 *)entity)->unk_1C | 0x02000200) & 0xFFFEFFFF;
        }
    } else {
        entity_spawn_variant_code = 1;
        source_entity = (void *)source_ref;

        type_data = find_or_retain_sprite_resource_slot(((S_80E3C98C_3 *)source_entity)->unk_13, 1);
        if (!((type_data != NULL) && (type_data->unk_01 != 0))) {
            type_data = find_or_retain_sprite_resource_slot(((S_80E3C98C_3 *)source_entity)->unk_13, 3);
            result = NULL;
            if (type_data == NULL) {
                return result;
            }
        }
        set_code_for_entity_mode(source_entity);
        create_entity = load_monster_resource_data(((S_80E3C98C_3 *)source_entity)->unk_13, type_data, 1);
        drain_cd_command_queue();
        spawn_mode = 4;
        if (spawn_data->unk_1C.at00_u32.v & 0x2000) {
            spawn_mode = 7;
        }
        entity = create_entity(spawn_mode, position->unk_24, position->unk_25, spawn_data->unk_88.as_s16);
        if (entity != NULL) {
            func_80042640(entity, ((S_80E3C98C_2 *)entity)->unk_13);
            ((S_80E3C98C_2 *)entity)->unk_14 = 0;
            ((S_80E3C98C_2 *)entity)->unk_1C = 0;
            copy_entity_record(entity, spawn_data);
            ((S_80E3C98C_2 *)entity)->unk_28++;
            ((S_80E3C98C_2 *)entity)->unk_13 = ((S_80E3C98C_3 *)source_entity)->unk_13;
            ((S_80E3C98C_6 *)(((S_80E3C98C_2_pre *)entity)[-1].unk_00))->unk_12 =
                ((S_80E3C98C_7 *)(((S_80E3C98C_3_pre *)source_entity)[-1].unk_00))->unk_12 & 3;
            ((S_80E3C98C_2 *)entity)->unk_14 |= 0x20000000;
            ((S_80E3C98C_2 *)entity)->unk_1C = (((S_80E3C98C_2 *)entity)->unk_1C | 0x02000000) & 0xFFFEFFFF;
        }
    }
    if (spawn_data->unk_14.at00_s32.v & 0x4000) {
        table_offset = find_entity_slot_by_field_ac(spawn_data);
        table_base = ((u8 *)dungeon_actor_ring_anchor);
        table_entry = (void *)(((s32)(table_offset << 0x10) >> 0xE) +
                               (long)table_base);

        previous_entity = table_entry->unk_AC;
        table_entry->unk_AC = entity;
        table_entry->unk_E4 = previous_entity;
    }
    result = NULL;
    if (entity != NULL) {
        result = (u8 *)entity - 0x20;
    }
    return result;
}
