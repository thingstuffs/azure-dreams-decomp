#include "dungeon/item/monster_resource_slots_g00325.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "dungeon/entity_spawn_variant_data.h"
#include "shared/record_ptrs.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/effect.h"
#include "engine/cd.h"
#include "dungeon/item/actor_target.h"
#include "dungeon/actor/effect.h"
#include "dungeon/item.h"
#include "dungeon/monster/manoeva.h"
#include "engine/entity.h"

#ifndef NULL
#define NULL 0
#endif



typedef struct S_80E3C98C_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80E3C98C_4;




extern void copy_entity_record();
extern void set_code_for_entity_mode();
extern MonsterFactory load_monster_code_module();

/* Create an entity from spawn data and update its tracked reference. */
void *spawn_manoeva_from_record(ActorRecord *body, ObjectPosition *unused1, SpriteFrameState *position, Rec_D_80082E80 *spawn_data) {
    s32 spawn_mode;
    s32 source_ref;
    u8 *table_base;
    MonsterFactory create_entity;
    s32 table_offset;
    PlayerRecord *table_entry;
    void *previous_entity;
    ActorRecord *source_entity;
    ActorRecord *entity;
    S_80E3C98C_4 *type_data;
    void *result;

    source_ref = spawn_data->unk_60.as_s32;
    if (source_ref > 0) {
        entity = create_mode_configured_object(((u32)spawn_data->unk_1C.at00_u32.v >> 0xD) & 1,
                               position->tile_x, position->tile_y,
                               spawn_data->unk_88.as_s16,
                               get_item_category_value(((s32)(((u16)spawn_data->unk_60.as_s32 - 1) << 0x10) >> 0xE)
                                   + ((u8 *)dungeon_ground_items)));
        if (entity != NULL) {
            entity->flags14 = 0;
            entity->flags1C = 0;
            copy_entity_record(entity, spawn_data);
            entity->flags14 |= 0x20000000;
            entity->flags1C =
                (entity->flags1C | 0x02000200) & 0xFFFEFFFF;
        }
    } else {
        entity_spawn_variant_code = 1;
        source_entity = (ActorRecord *)source_ref;

        type_data = find_or_retain_sprite_resource_slot(source_entity->species, 1);
        if (!((type_data != NULL) && (type_data->unk_01 != 0))) {
            type_data = find_or_retain_sprite_resource_slot(source_entity->species, 3);
            result = NULL;
            if (type_data == NULL) {
                return result;
            }
        }
        set_code_for_entity_mode(source_entity);
        create_entity = load_monster_code_module(source_entity->species, type_data, 1);
        drain_cd_command_queue();
        spawn_mode = 4;
        if (spawn_data->unk_1C.at00_u32.v & 0x2000) {
            spawn_mode = 7;
        }
        entity = create_entity(spawn_mode, position->tile_x, position->tile_y, spawn_data->unk_88.as_s16);
        if (entity != NULL) {
            func_80042640(entity, entity->species);
            entity->flags14 = 0;
            entity->flags1C = 0;
            copy_entity_record(entity, spawn_data);
            entity->hp++;
            entity->species = source_entity->species;
            NODE_HEADER(entity)->sprite->clut =
                NODE_HEADER(source_entity)->sprite->clut & 3;
            entity->flags14 |= 0x20000000;
            entity->flags1C = (entity->flags1C | 0x02000000) & 0xFFFEFFFF;
        }
    }
    if (spawn_data->unk_14.at00_s32.v & 0x4000) {
        table_offset = find_entity_slot_by_field_ac(spawn_data);
        table_base = ((u8 *)dungeon_actor_ring_anchor);
        table_entry = (void *)(((s32)(table_offset << 0x10) >> 0xE) +
                               (long)table_base);

        previous_entity = table_entry->actor.unk_AC.address;
        table_entry->actor.unk_AC.address = entity;
        table_entry->menu_alternate[0] = previous_entity;
    }
    result = NULL;
    if (entity != NULL) {
        result = NODE_HEADER(entity);
    }
    return result;
}
