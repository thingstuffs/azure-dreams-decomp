#include "shared/actor_property_flags.h"
/* Select dungeon spawn tiles and advance staged entity loading.
 * Evidence: proven (string literals).
 * dungeon/engine#g0246 J1[80089000]
 * B1@0x80089000; B1@0x80089080; partial span, complete TU edges unknown.
 */
#include "dungeon/actor/entity_spawn_load.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "engine/scene.h"
#include "dungeon/level.h"

/* Tries random free room tiles, then scans the floor, falling back to valid input coordinates or (1, 1). */
s32 select_dungeon_spawn_tile(u8 *x_out, u8 *y_out)
{
    u16 tile;
    s16 areaIndex;
    s16 x;
    s16 y;
    s32 attempts;
    s32 result;
    DungeonArea *area;
    s16 *limits;
    DungeonArea *areas;

    attempts = 0x100;
    limits = floor_generation_state;
    areas = (DungeonArea *)dungeon_rooms;

    do {
        areaIndex = (u16)generate_random_value() % limits[3];
        area = (DungeonArea *)((areaIndex * (s32)sizeof(*area)) + (unsigned long)areas);
        if (area->enabled != 0) {
            x = (u32)(generate_random_value() & 0xFFFF) % area->width;
            y = (u32)(generate_random_value() & 0xFFFF) % area->height;
            x += area->x;
            y += area->y;
            if ((s16)get_offset_map_cell_value_and_flags((s16)(x - 1), y, 0, &tile) != 0) {
                if ((tile & 0xF720) == 0) {
                    result = areaIndex;
                    *x_out = x;
                    *y_out = y;
                    return result;
                }
            }
        }
        attempts--;
    } while (attempts > 0);

    for (y = 1; y < 0x3F; y++) {
        for (x = 1; x < 0x3F; x++) {
            if ((s16)get_offset_map_cell_value_and_flags((s16)(x - 1), y, 0, &tile) != 0) {
                if ((tile & 0xF720) == 0) {
                    result = 0;
                    *x_out = x;
                    *y_out = y;
                    return result;
                }
            }
        }
    }

    if ((u32)(*x_out - 1) < 0x3E) {
        if ((u32)(*y_out - 1) < 0x3E) {
            result = 0;
            return result;
        }
    }
    *x_out = 1;
    *y_out = 1;
    result = 0;
    return result;
}

/* Advances staged entity loading and replaces the entity while transferring its state. */
s32 advance_staged_entity_load(s32 unused, ActorRecord *entity)
{
    S_800A504C_0 *base = (S_800A504C_0 *)((DungeonState *)&g_dungeon_status);
    s32 count = base->unk_0A.s;
    s32 offset;
    s32 load_result;
    u8 *load_spawned;
    s32 saved_word_5c;
    s32 saved_word_58;
    s32 angle;
    s32 global_flags;
    u16 data_flags;
    u16 remaining_count;
    s32 update_flags;
    s32 update_flags_2;
    s32 flags_result;
    S_800A504C_6 *global_page;
    u8 *copy_call_entity;
    s32 copy_call_zero;
    s32 scale;
    s32 replace_call_zero;
    s32 load_kind;
    void *spawned;
    u8 *replacement;
    ObjectNodeHeader *shifted;
    u8 *entity_data;
    S_800A504C_2_pre *mode_page;
    S_800A504C_5 *record;
    u8 *record_data;
    u8 *tail_dst;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    SpawnFunc spawn;

    if (count != 1) {
        return 0;
    }
    if (has_enough_available_runtime_nodes(8) == 0) {
        return 0;
    }

    mode_page = (S_800A504C_2_pre *)0x800E0000;
    if (entity->flags14 & 0x4000) {
        switch (mode_page[-1].unk_00) {
        case 0:

        if (read_sound_mode_blocking_status(4) != 0) {
            return 0;
        }
        spawned = (u8 *)find_or_retain_sprite_resource_slot(entity->species, 2);
        if (spawned == NULL) {
            return 0;
        }
        load_result = queue_cd_resource(entity->species);
        load_spawned = spawned;
        loaded_entity_sprite_resource = load_result;
        load_monster_code_module(entity->species, load_spawned, 0);
        entity_resource_read_complete[0] = 0;
        Control_CD(0xFF, set_byte_one, entity_resource_read_complete);
        mode_page[-1].unk_00 = (s16)((u16)mode_page[-1].unk_00 + 1);
        break;

case 1:
        if (entity_resource_read_complete[0] != 0) {
            func_80047E30();
            mode_page[-1].unk_00 = (s16)((u16)mode_page[-1].unk_00 + 1);
            break;
        }
        return 0;

case 2:
        spawned = (u8 *)find_or_retain_sprite_resource_slot(entity->species, 2);
        if (spawned == NULL) {
            return 0;
        }
        entity_data = ((S_800A504C_1_pre *)entity)[-1].unk_00;
        spawn = load_monster_code_module(entity->species, spawned, 1);
        spawned = spawn(6, entity_data[0x24], entity_data[0x25],
                        (s16)(((S_800A504C_1 *)entity)->unk_88 - 0x20));
        if (spawned == NULL) {
            return 0;
        }
        base = (S_800A504C_0 *)entity;
        tail_dst = spawned;
        saved_word_5c = ((S_800A504C_3 *)tail_dst)->unk_5C;
        saved_word_58 = ((S_800A504C_3 *)tail_dst)->unk_58;
        copy_dst = tail_dst;
        copy_src = (u8 *)entity;
        copy_end = ((u8 *)entity) + 0x80;
        do {
            *(EntityCopyBlock *)copy_dst = *(EntityCopyBlock *)copy_src;
            copy_src += sizeof(EntityCopyBlock);
            copy_dst += sizeof(EntityCopyBlock);
        } while (copy_src != copy_end);
        *(EntityCopyTail *)copy_dst = *(EntityCopyTail *)copy_src;
        ((S_800A504C_4 *)spawned)->unk_4C = 0;
        ((S_800A504C_4 *)spawned)->unk_50 = 0;
        ((S_800A504C_4 *)spawned)->unk_5C = saved_word_5c;
        ((S_800A504C_4 *)spawned)->unk_58 = saved_word_58;
        func_80042640(spawned, ((S_800A504C_4 *)spawned)->unk_10.at03.v);

        copy_call_entity = spawned;
        copy_call_zero = 0;
        scale = 0x1000;
        entity_data = ((S_800A504C_4_pre *)spawned)[-1].unk_00;
        ((S_800A504C_2 *)entity_data)->unk_1E = scale;
        ((S_800A504C_2 *)entity_data)->unk_1C = scale;
        ((S_800A504C_4 *)spawned)->unk_14 &= -8;
        ((S_800A504C_4 *)spawned)->unk_1C &= -8;
        ((S_800A504C_4 *)spawned)->unk_14 |= entity->flags14 & 7;
        ((S_800A504C_4 *)spawned)->unk_1C |= entity->flags1C & 7;
        apply_actor_template_and_class(copy_call_entity, ((S_800A504C_4 *)spawned)->unk_10.at03.v,
                      copy_call_zero);
        copy_entity_record(spawned, entity);
        ((S_800A504C_4 *)spawned)->unk_14 &= ~0x4000;

        ((S_800A504C_3 *)tail_dst)->unk_8C = base->unk_8C;
        ((S_800A504C_3 *)tail_dst)->unk_90 = base->unk_90;
        ((S_800A504C_3 *)tail_dst)->unk_94 = base->unk_94;
        ((S_800A504C_3 *)tail_dst)->unk_98 = base->unk_98;
        ((S_800A504C_3 *)tail_dst)->unk_9A = base->unk_9A;
        ((S_800A504C_3 *)tail_dst)->unk_9B = base->unk_9B;

        offset = find_entity_slot_by_field_ac(entity);
        record = ((S_800A504C_5 *)primary_actor_record);
        offset = (offset << 16) >> 14;
        offset += (s32)record;
        record = (S_800A504C_5 *)offset;
        record->unk_AC = spawned;
        update_map_cell_flags_with_item_limit(entity_data[0x24], entity_data[0x25], 0x300);
        unlink_entity_node(spawned);
        shifted = spawned - 0x20;
        unlink_node(shifted);
        update_flags = 0x80000000;
        flags_result = ((S_800A504C_4 *)shifted)->unk_10.at00.v;
        global_page = (S_800A504C_6 *)0x80080000;
        ((S_800A504C_4 *)shifted)->unk_10.at00.v = flags_result | update_flags;
        update_flags = ((S_800A504C_1_pre *)entity)[-1].unk_12;
        ((S_800A504C_1_pre *)entity)[-1].unk_12 = update_flags | 0x8000;
        update_flags_2 = global_page->unk_14A0;
        flags_result = 0;
        ((S_800A504C_7_pre *)D_800E0000)[-1].unk_00 = 0;
        global_page->unk_14A0 = update_flags_2 | 0x8000;
        return flags_result;
        default:
            return 0;
        }
    } else {
        switch (mode_page[-1].unk_00) {
        case 0:

        load_kind = 3;
        replacement = (u8 *)find_or_retain_sprite_resource_slot(entity->species - 1,
                                      load_kind);
        if (replacement != NULL) {
            entity->species--;
            func_8003E188(entity->species, 0);
            sprite_resource_base = D_80023000;
            load_result = begin_sprite_resource_load_with_completion_flag(entity->species, sprite_resource_completion_flag);
            load_spawned = replacement;

            loaded_entity_sprite_resource = load_result;
            load_monster_code_module(entity->species, load_spawned, 0);
            entity_resource_read_complete[0] = 0;
            Control_CD(0xFF, set_byte_one, entity_resource_read_complete);
        }
        mode_page[-1].unk_00 = (s16)((u16)mode_page[-1].unk_00 + 1);
        break;

case 1:
        if (entity_resource_read_complete[0] == 0) {
            return 0;
        }
        if (loaded_entity_sprite_resource != 0) {
            register_and_upload_sprite_resource(entity->species, loaded_entity_sprite_resource);
        }

        mode_page[-1].unk_00 = (s16)((u16)mode_page[-1].unk_00 + 1);
        break;

case 2:
        replacement = (u8 *)find_or_retain_sprite_resource_slot(entity->species, 3);
        if (replacement == NULL) {
            return 0;
        }
        entity_data = ((S_800A504C_1_pre *)entity)[-1].unk_00;
        spawn = load_monster_code_module(entity->species, replacement, 1);
        replacement = spawn(1, entity_data[0x24], entity_data[0x25],
                        (s16)(((S_800A504C_1 *)entity)->unk_88 - 0x20));
        if (replacement != NULL) {
            ((S_800A504C_4 *)replacement)->unk_14 |= ACTOR_PARTY_MEMBER;
            offset = find_entity_slot_by_field_ac(entity);
            record = ((S_800A504C_5 *)primary_actor_record);
            offset = (offset << 16) >> 14;
            offset += (s32)record;
            record = (S_800A504C_5 *)offset;
            record_data = record->unk_D0;
            record->unk_AC = replacement;
            record_data[0] = entity->species;
            (*(u8 * *)((u8 *)familiar_record_slots + (record_data[3] & 0x1F) * 4)) = replacement;

            entity_data = ((S_800A504C_4_pre *)replacement)[-1].unk_00;
            ((S_800A504C_2 *)entity_data)->unk_1E = 0x1000;
            ((S_800A504C_2 *)entity_data)->unk_1C = 0x1000;
            func_80042640(replacement, ((S_800A504C_4 *)replacement)->unk_10.at03.v);
            copy_call_entity = replacement;
            replace_call_zero = 0;
            ((S_800A504C_4 *)replacement)->unk_14 &= -8;
            ((S_800A504C_4 *)replacement)->unk_1C &= -8;
            ((S_800A504C_4 *)replacement)->unk_14 |= entity->flags14 & 7;
            ((S_800A504C_4 *)replacement)->unk_1C |= entity->flags1C & 7;
            apply_actor_template_and_class(copy_call_entity, ((S_800A504C_4 *)replacement)->unk_10.at03.v,
                          replace_call_zero);
            copy_entity_record(replacement, entity);

            if (((S_800A504C_4 *)replacement)->unk_43 < 0x40) {
                TablePage *table_page = (TablePage *)0x80010000;
                s32 table_index = ((S_800A504C_4 *)replacement)->unk_43;
                u8 table_value = ((S_800A504C_4 *)replacement)->unk_10.at03.v;
                table_page->table84[table_index].value = table_value;
                table_page->table4[table_index].value = table_value;
            }
            retain_spawn_resource(((S_800A504C_4 *)replacement)->unk_10.at03.v, 3);
            replay_actor_status_slots(replacement);
            angle = ((S_800A504C_1 *)entity)->unk_2A;
            (*(u16 *)((u8 *)replacement + 0x2A)) = angle;
            offset = ((g_game_work.view.camera_rotation.parts.viewAngle + (s16)angle + 0x100) >> 9) & 7;
            select_indirect_table_entry(entity_data, ((u8 *)((S_800A504C_2 *)entity_data)->unk_2C)[offset],
                          ((S_800A504C_2 *)entity_data)->unk_04);
            data_flags = ((S_800A504C_2 *)entity_data)->unk_14;
            sprite_resource_base = dungeon_resource_buffer;
            ((S_800A504C_2 *)entity_data)->unk_14 = data_flags & 0xFFFE;
            remaining_count = base->unk_0A.u;
            staged_spawn_count = count;
            base->unk_0A.s = (s16)(remaining_count - 1);
            (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
            global_flags = object_flag_block.flags;
            entity->unk_90.value = 0;
            object_flag_block.flags = global_flags | 0x8000;
        }
        break;
        default:
            return 0;
        }
    }
    return 0;
}
