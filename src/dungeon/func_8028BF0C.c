#include "modules/dungeon_floor_spawns.h"

void restore_spawns_and_place_floor_traps(void) {
    u8 x;
    u8 y;
    u8 *floor_config;
    floor_spawns_isolated_8028BF0C_SpawnPosition *position;
    floor_spawns_isolated_8028BF0C_SpawnMeta *meta;
    s32 *limits;
    u32 *initial;
    s32 slot;
    s32 spawn_limit;
    s32 trap_budget;
    s32 trap_cost;
    s32 value;
    s32 availability;
    s32 trap_state;
    s16 floor_height;
    u32 initial_value;
    s32 flag_bits;
    u32 shifted_flag_bits;
    u16 flags;
    u8 trap_type;
    u8 existing_type;
    s16 store_type;
    u8 spawn_variant;
    u8 spawn_marker;
    s32 spawn_height;
    floor_spawns_isolated_8028BF0C_S_8001EF0C_0 *object;

    slot = 0;
    initial = D_800835E4->initial;
    limits = (s32 *)(initial + 1);
    meta = ((floor_spawns_isolated_8028BF0C_SpawnMeta *)D_800E3648);
    position = D_800E39C8;
    do {
        if (meta[slot].state == 0x13) {
            existing_type = meta[slot].type;
            availability = find_or_retain_sprite_resource_slot(existing_type, 1);
            if (availability != 0) {
                object = load_monster_resource_data(existing_type, availability, 1)
                (0, position[slot].x, position[slot].y, -0x400);
                if (object != 0) {
                    retain_spawn_resource(existing_type, 1);
                    func_80042640(object, existing_type);
                    object->unk_43.s = 0xFF;
                    object->unk_12 = 0;
                    initial_value = initial[(s8)meta[slot].unk2];
                    object->unk_18 = initial_value;
                    if (initial_value >= (u32)limits[object->unk_11]) {
                        s32 *loop_limits;
                        loop_limits = D_800835E8;
                        do {
                            raise_entity_level(object, 0);
                        } while ((u32)loop_limits[object->unk_11] <=
                                 object->unk_18);
                    }
                    object->unk_43.u = generate_random_value();
                }
            }
            *(s32 *)&meta[slot] = 0;
        }
        slot++;
    } while (slot < 0x20);

    floor_config = (u8 *)D_80081468;
    if (((floor_spawns_isolated_8028BF0C_S_8001EF0C_1 *)floor_config)->unk_06 == 1) {
        spawn_limit = (generate_random_value() & 3) + 4;
    } else {
        spawn_limit = ((floor_spawns_isolated_8028BF0C_S_8001EF0C_1 *)floor_config)->unk_06 / 2 + (generate_random_value() & 3);
    }
    if (spawn_limit >= 0x21) {
        spawn_limit = 0x20;
    }

    value = generate_random_value();
    slot = 0;
    trap_state = 0x15;
    position = D_800E39C8;
    trap_budget = ((s16 *)D_8008146C)[0] / 2 + (value & 0x3F);
    meta = ((floor_spawns_isolated_8028BF0C_SpawnMeta *)D_800E3648);

    for (; slot < 0x20; slot++) {
        if (meta[slot].state == trap_state) {
            x = position[slot].x;
            y = position[slot].y;
            trap_type = meta[slot].type;
            spawn_variant = meta[slot].unk2;
            spawn_marker = meta[slot].unk3;
            spawn_height = -0x400;
        } else {
            if ((D_800E3D6C[0] & 8) || slot >= spawn_limit) continue;
            meta[slot].state = 0;
            meta[slot].type = 0;
            trap_budget += generate_random_value() & 0xF;
            store_type = random_dungeon_range_16(1, 0x13);
            trap_type = store_type;
            flags = *(u16 *)(D_800735C4[0] + (trap_type * 0xC));
            flag_bits = flags & 0x3000;
            shifted_flag_bits = flag_bits << 16;
            if (flag_bits == 0x3000) continue;
            trap_cost = (shifted_flag_bits >> 26) + 4;
            if (trap_budget < trap_cost) continue;
            trap_budget -= trap_cost;
            if (!((D_800E296C & 0x20000000) || ((u8)(trap_type - 0xF) >= 2))) continue;
            meta[slot].state = trap_state;
            meta[slot].type = store_type;
            do {
            } while ((s16)select_dungeon_spawn_tile(&x, &y) < 0);
            position[slot].x = x;
            position[slot].y = y;
            spawn_variant = (generate_random_value() & 7) | 4;
            spawn_marker = 0x80;
            spawn_height = -0x400;
        }
        meta[slot].unk2 = spawn_variant;
        meta[slot].unk3 = spawn_marker;
        floor_height = sample_terrain_surface_height((x << 6) | 0x20,
                               (y << 6) | 0x20,
                               spawn_height);
        position[slot].unk12 = floor_height;
        position[slot].unk10 = floor_height;
        position[slot].flags = 0;
        cycle_map_cell_flags(x, y, 0x20);
        {
            u8 *lookup_base = 0;
            s32 table_index;

            table_index = trap_type;
            lookup_base = D_800DF258;
            value = *(s32 *)(lookup_base + (table_index << 2));
        }
        if (value < 0) {
            func_8003DB94(&position[slot], value, 0);
            flags = position[slot].flags;
            position[slot].flags = flags | 0x840;
            if (value & 0x20000000) {
                position[slot].flags = flags | 0x940;
            }
        } else {
            if (value != 0) {
                position[slot].value = value | 0x80000000;
            }
            position[slot].flags |= 0x800;
        }
        position[slot].zero = 0;
    }
}
