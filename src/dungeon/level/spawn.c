#include "dungeon/level/tile_flags.h"
/* Floor item selection and placement, saved monster restoration, traps, and floor label sprites. */
#include "shared/object_node.h"
#include "dungeon/level/spawn.h"
#include "shared/item_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/level.h"
#include "dungeon/actor.h"
#include "dungeon/system.h"
#include "dungeon/actor/effect.h"
#include "dungeon/player/object.h"

/* Searches all 64 ground-item slots for a nonempty item at X/Y, excluding the supplied slot. */
s32 is_floor_item_tile_occupied(s32 excluded_slot, s16 x, s16 y)
{
    s32 slot;

    for (slot = 0; slot < 64; slot++) {
        if ((excluded_slot != slot) &&
            (dungeon_ground_items[slot].kind != ITEM_KIND_NONE) &&
            (((floor_spawns_isolated_8028B110_DungeonPosition *)dungeon_ground_item_positions)[slot].x == x) &&
            (((floor_spawns_isolated_8028B110_DungeonPosition *)dungeon_ground_item_positions)[slot].y == y)) {
            return 1;
        }
    }
    return 0;
}

/* Restores loaded item tiles or places random floor items, applies special drops, and sets their heights. */
void populate_floor_item_records(void)
{
    u8 tile_x;
    u8 tile_y;
    u8 item_category;
    u8 item_subtype;
    s32 count;
    s32 found_status;
    s32 crystal_pending;
    s16 category18_pending;
    s32 slot_limit;
    s32 spawn_index;
    s32 special_flag;
    s32 spawn_check;
    floor_spawns_isolated_8028B18C_DungeonGroup *item_category_table;
    floor_spawns_isolated_8028B18C_DungeonRecord *item_record;
    DungeonItemEntry *item_state;
    floor_spawns_isolated_8028B18C_DungeonRecord *saved_record;
    floor_spawns_isolated_8028B18C_DungeonRecord *spawn_records;
    u8 *setup_globals;
    if (floor_loaded_content_flags[0] & 2) {
        count = 0;
        saved_record = (floor_spawns_isolated_8028B18C_DungeonRecord *)dungeon_ground_item_positions;
        item_state = (DungeonItemEntry *)((u8 *)dungeon_ground_items);
        do {
            if (item_state->unk_00 != 0) {
                cycle_map_cell_flags(saved_record->x, saved_record->y, TILE_HAS_ITEM);
            }
            saved_record++;
            count++;
            item_state++;
        } while (count < 0x40);
        return;
    }

    setup_globals = (u8 *)0x80010000;
    *(u16 *)(setup_globals + 0x3626) = *(u16 *)(setup_globals + 0x3624);
    *(u16 *)(setup_globals + 0x209E) = *(u16 *)(setup_globals + 0x209C);
    ((s8 *)floor_special_item_selected)[0] = 0;
    *(u16 *)(setup_globals + 0x3626) += (generate_random_value() & 3) + 0x33;
    *(u16 *)(setup_globals + 0x209E) += (generate_random_value() & 3) + 0x33;

    if (floor_generation_state[3] == 1) {
        s32 limit_roll;

        crystal_pending = 0;
        limit_roll = generate_random_value() & 7;
        slot_limit = limit_roll + 8;
    } else {
        s32 limit_roll;
        s32 base_limit;

        crystal_pending = 0;
        limit_roll = generate_random_value() & 3;
        base_limit = (s16)floor_generation_state[3] / 2;
        slot_limit = base_limit + limit_roll;
    }

    if ((generate_random_value() & 3) == 0) {
        crystal_pending = *(s16 *)0x8001209E >= 0x101;
    }
    category18_pending = 0;
    if ((generate_random_value() & 3) == 0) {
        category18_pending = *(s16 *)0x80013626 >= 0x101;
    }

    if (*(s32 *)0x80012090 == 0) {
        spawn_check = count_matching_packed_entity_keys(6, 3);
        if ((s16)spawn_check < 2) {
            if ((generate_random_value() & 3) == 0) {
                spawn_index = (s16)find_first_empty_floor_item_slot();
                if (spawn_index >= 0) {
                    do {
                        do {
                        } while ((s16)select_dungeon_spawn_tile(&tile_x, &tile_y) < 0);
                    } while (is_floor_item_tile_occupied(spawn_index, tile_x, tile_y) != 0);

                    {
                        s32 *spawn_table = (s32 *)((u8 *)dungeon_ground_items);
                        spawn_table[spawn_index] = 0x603;
                    }
                    spawn_records = (floor_spawns_isolated_8028B18C_DungeonRecord *)dungeon_ground_item_positions;
                    spawn_records[spawn_index].x = tile_x;
                    spawn_records[spawn_index].y = tile_y;
                    cycle_map_cell_flags(spawn_records[spawn_index].x,
                                  spawn_records[spawn_index].y, TILE_HAS_ITEM);
                }
            }
        }
    }

    count = 0;
    spawn_check = (s32)((u8 *)0x80010000);
    item_category_table = ((floor_spawns_isolated_8028B18C_DungeonGroup *)item_category_groups);
    item_state = (DungeonItemEntry *)((u8 *)dungeon_ground_items);
    item_record = (floor_spawns_isolated_8028B18C_DungeonRecord *)dungeon_ground_item_positions;
main_loop:
    if (item_state->kind == ITEM_KIND_NONE) {
        if (count >= slot_limit) {
            goto cleanup;
        }

        found_status = (s16)select_floor_item_with_special_overrides(&item_category, &item_subtype, 0, 0);
        if (found_status != 0 || item_category != ITEM_KIND_NONE) {
            if (found_status == 0) {
                special_flag = crystal_pending;
                if (special_flag != 0) {
                    s32 page_value;

                    page_value = ((generate_random_value() & 0xF) == 0) ? ITEM_BIG_PITA_FRUIT : ITEM_PITA_FRUIT;
                    item_subtype = page_value;
                    crystal_pending = 0;
                    page_value = *(u16 *)(((u8 *)spawn_check) + 0x209E);
                    item_category = ITEM_KIND_FRUIT;
                    page_value &= 0xF;
                    *(u16 *)(((u8 *)spawn_check) + 0x209E) = page_value;
                } else {
                    special_flag = category18_pending;
                    if (special_flag != 0) {
                        u32 item_flags;

                        item_category = ITEM_KIND_EGG;
                        item_subtype = floor_species_pool[generate_random_value() & 0x1F];
                        item_flags = item_category_table[ITEM_KIND_EGG].entries[item_subtype].flags;
                        if ((item_flags & 0x10) != 0 &&
                            (item_category_table[ITEM_KIND_FAMILIAR].entries[item_subtype].flags & 0x80) != 0 &&
                            item_subtype >= 2) {
                            item_subtype++;
                        }
                        category18_pending = 0;
                        *(u16 *)(((u8 *)spawn_check) + 0x3626) &= 0x3F;
                    }
                }
            }

            item_state->kind = item_category;
            item_state->unk_00 = item_subtype;
            init_random_floor_item_parameters(item_state);

            do {
            } while ((s16)select_dungeon_spawn_tile(&tile_x, &tile_y) < 0);

            if (is_floor_item_tile_occupied(count, tile_x, tile_y) != 0) {
                item_state->kind = ITEM_KIND_NONE;
            } else {
                item_record->x = tile_x;
                item_record->y = tile_y;
                item_record->field4 = get_surface_height_at_coordinates((tile_x << 6) | 0x20,
                                                    (tile_y << 6) | 0x20);
                item_record->field7 = 0;
                cycle_map_cell_flags(tile_x, tile_y, TILE_HAS_ITEM);
                item_record->field8 = get_item_category_value(item_state);
            }
        }
    } else {
        tile_x = item_record->x;
        tile_y = item_record->y;
        init_random_floor_item_parameters(item_state);
        item_record->field4 = get_surface_height_at_coordinates((tile_x << 6) | 0x20,
                                            (tile_y << 6) | 0x20);
        item_record->field7 = 0;
        cycle_map_cell_flags(tile_x, tile_y, TILE_HAS_ITEM);
        item_record->field8 = get_item_category_value(item_state);
    }

    item_state++;
    count++;
    item_record++;
    if (count < 0x40) {
        goto main_loop;
    }

cleanup:
    if (count < 0x40) {
        DungeonItemEntry *cleanup_base;
        DungeonItemEntry *cleanup_state;

        cleanup_base = (DungeonItemEntry *)((u8 *)dungeon_ground_items);
        cleanup_state = cleanup_base + count;
cleanup_loop:
            cleanup_state->kind = ITEM_KIND_NONE;
            (cleanup_state++)->unk_00 = 0;
            count++;
        if (count < 0x40) {
            goto cleanup_loop;
        }
    }
    generate_random_dungeon_item_drops();

    return;
}

/* Selects a floor-specific special item once when eligible, otherwise uses the weighted item table. */
s32 select_floor_item_with_special_overrides(s8 *out_group, s8 *out_index, s32 unused, s32 skip_special) {
    u8 special_selected;
    special_selected = floor_special_item_selected[0];

    if ((special_selected == 0) && (skip_special == 0) && (*(s32 *)0x80012090 == 0)) {
        if (((s16 *)current_dungeon_floor)[0] == 12) {
            if (((floor_spawns_isolated_8028B660_S_8001E660_0 *)(dungeon_actor_ring_anchor))->unk_FB == 0) {
                *out_group = 12;
                *out_index = ITEM_BLUE_COLLAR;
                floor_special_item_selected[0] = 1;
                return 1;
            }
        } else if (((s16 *)current_dungeon_floor)[0] == 15) {
            if ((test_resident_bit(0x145E) != 0) && (test_resident_bit(0x1460) == 0)
                && ((has_recorded_value_pair(0xD, ITEM_GURUS_POT) << 0x10) == 0)) {
                *out_group = 0xD;
                *out_index = ITEM_GURUS_POT;
                floor_special_item_selected[0] = 1;
                return 1;
            }
        } else if (((s16 *)current_dungeon_floor)[0] == 28) {
            if ((test_resident_bit(0xFC3) != 0) && (test_resident_bit(0xFAD) == 0) && ((has_recorded_value_pair(ITEM_KIND_HERB, ITEM_HEALING_HERB) << 0x10) == 0)) {
                *out_group = ITEM_KIND_HERB;
                *out_index = ITEM_HEALING_HERB;
                floor_special_item_selected[0] = 1;
                return 1;
            }
        } else if (((s16 *)current_dungeon_floor)[0] == 20) {
            if ((test_resident_bit(0xAC) != 0) && (test_resident_bit(0x12C6) == 0) && ((has_recorded_value_pair(0xD, ITEM_BLUE_CAPE) << 0x10) == 0)) {
                *out_group = 0xD;
                *out_index = ITEM_BLUE_CAPE;
                floor_special_item_selected[0] = 1;
                return 1;
            }
        }
        select_weighted_floor_item(out_group, out_index);
        return 0;
    } else {
        select_weighted_floor_item(out_group, out_index);
        return 0;
    }
}

/* Sets an item's parameter and flags from category-specific random rolls. */
void init_random_floor_item_parameters(void *entity_data) {
    floor_spawns_isolated_8028B824_S_8001E824_0 *entity = entity_data;
    s16 output_flags;
    s16 combined_flags;
    s16 output_value;
    s32 minus_128;
    s32 adjusted_value;
    u8 case_value;

    output_flags = 0;
    case_value = entity->unk_01;
    output_value = output_flags;
    switch (case_value) {
    case ITEM_KIND_BALL:
        output_value = 1;
        if (entity->unk_00 != ITEM_ACID_RAIN_BALL) {
            output_value = (generate_random_value() & 7) | 4;
        }
        output_flags = -0x80;
        break;
    case ITEM_KIND_SWORD:
        if (entity->unk_00 == ITEM_DARK_SWORD) {
            output_flags |= 0x40;
        }
    case ITEM_KIND_SHIELD:
        if (!(generate_random_value() & 3)) {
            adjusted_value = (generate_random_value() & 3) - 1;
            output_value = adjusted_value;
            if (adjusted_value < 0) {
                output_flags |= 0x40;
            }
        }
    case ITEM_KIND_WAND:
        minus_128 = -0x80;
        combined_flags = output_flags | minus_128;
        output_flags = combined_flags;
        if (generate_random_value() & 7) {
            break;
        }
        output_value = -1;
        output_flags = combined_flags | 0x40;
        break;
    case ITEM_KIND_EGG:
        output_value = ((u32)(generate_random_value() & 0xFFFF) % 40U) + 0x3C;
        break;
    case ITEM_KIND_HERB:
    default:
        break;
    }
    entity->unk_02 = output_value;
    entity->unk_03 = output_flags;
}

/* Clears the 64 words of dungeon_ground_items in reverse order. */
void clear_dungeon_cell_entries(void) {
    s32 entry_index;

    for (entry_index = 0x3F; entry_index >= 0; entry_index--) {
        ((int *)dungeon_ground_items)[entry_index] = 0;
    }
}

/* Builds cumulative category weights from eligible item definitions and their rarity flags. */
void build_cumulative_item_weights(void)
{
    s32 total_weight;
    s32 category_index;
    s32 item_index;
    s32 item_flags;
    s32 item_weight;
    s32 weight_bits;
    s32 weight_kind;

    total_weight = 0;
    for (category_index = 1; category_index < 0x13; category_index++) {
        for (item_index = 1; item_index < ((floor_spawns_isolated_8028B994_DungeonGroup *)item_category_groups)[category_index].count; item_index++) {
            item_flags = ((floor_spawns_isolated_8028B994_DungeonGroup *)item_category_groups)[category_index].entries[item_index].flags;
            if (item_flags & 0x10) {
                continue;
            }
            if ((item_flags & 0x40) && *(s32 *)0x80012090 != 2) {
                continue;
            }
            weight_bits = ((floor_spawns_isolated_8028B994_DungeonGroup *)((u8 *)((floor_spawns_isolated_8028B994_DungeonGroup *)item_category_groups) + (((category_index << 3) + (category_index << 1)) << 1)))->entries[item_index].flags & 0x3000;
            weight_kind = (weight_bits / 0x1000) & 3;
            item_weight = 0x80;
            if (weight_kind != 0) {
                item_weight = 0x55;
                if (weight_kind != 1) {
                    item_weight = 1;
                    if (weight_kind == 2) {
                        item_weight = 0x20;
                    }
                }
            }
            total_weight += item_weight;
        }
        spawn_category_weight_totals[category_index] = total_weight;
    }
    spawn_category_weight_totals[category_index] = total_weight;
}

/* Selects an eligible category and item by rarity weight, writing zeros if the scan finds none. */
s32 select_weighted_floor_item(s8 *category_out, s8 *item_out) {
    s32 category_index;
    s32 selected_category;
    s32 rarity;
    s32 category_scale_or_weight;
    u8 *table_cursor_or_item_offset;
    s32 item_index;
    s32 scan_value;
    u16 *category_threshold;
    u16 *thresholds;
    u16 *entry;
    u16 item_flags;
    s32 cumulative_weight;
    u32 rng_result;
    u16 random_weight;
    unsigned long table_base_or_mode;
    u8 *item_category_table;
    u8 *category_entry;
    u8 *item_offset;

    rng_result = generate_random_value();
    thresholds = (u16 *)spawn_category_weight_totals;
    random_weight = thresholds[19];
    random_weight = (rng_result & 0xFFFF) % random_weight;
    category_index = 1;
    item_offset = (u8 *)thresholds;
    category_threshold = (u16 *)(item_offset + 2);
    category_scale_or_weight = random_weight & 0xFFFF;
    /*
     * BUG: equality selects the preceding category, but its item scan uses an exclusive upper bound. A roll at
     * a cumulative boundary falls through to item 0/0; equality should advance to the next category.
     */
    while (1) {
        if (!(*category_threshold < (u32)category_scale_or_weight)) {
            item_index = 1;
            break;
        }
        category_index += 1;
        category_threshold += 1;
        if (category_index >= 0x13) {
            item_index = 1;
            break;
        }
    }
    category_scale_or_weight = category_index * 4;
    entry = &((u16 *)item_offset)[category_index];
    table_base_or_mode = (unsigned long)item_category_groups;
    scan_value = category_scale_or_weight + category_index;
    scan_value *= 4;
    table_cursor_or_item_offset = (u8 *)(scan_value + table_base_or_mode);
    entry--;
    cumulative_weight = *entry;
    if (item_index < table_cursor_or_item_offset[2]) {
        scan_value = category_index << 16;
        item_category_table = (u8 *)table_base_or_mode;
        table_base_or_mode = 2;
        category_entry = table_cursor_or_item_offset;
        selected_category = scan_value >> 16;
        item_offset = (u8 *)0x14;
loop_6:
        item_flags = *(u16 *)(item_offset + ((floor_spawns_isolated_8028BAA4_ItemCategoryRow *)(item_category_table
            + ((category_scale_or_weight + category_index) * 4)))->item_table);
        if (!(item_flags & 0x10)) {
            if ((item_flags & 0x40) && (*(s32 *)0x80012090) != (s32)table_base_or_mode) {
                category_scale_or_weight = category_index * 4;
                scan_value = item_category_table[((category_scale_or_weight + category_index) * 4) + 2];
            } else {
                scan_value = *(u16 *)(item_offset + ((floor_spawns_isolated_8028BAA4_ItemCategoryRow *)category_entry)->item_table) & 0x3000;
                if (scan_value < 0) {
                    scan_value += 0xFFF;
                    rarity = (scan_value >> 0xC) & 3;
                    category_scale_or_weight = 0x80;
                    if (rarity != 0) {
                        category_scale_or_weight = 0x55;
                        if (rarity != 1) {
                            category_scale_or_weight = 1;
                            if (rarity == (s32)table_base_or_mode) {
                                category_scale_or_weight = 0x20;
                            }
                        }
                    }
                    cumulative_weight += category_scale_or_weight;
                    if (random_weight < (u32)(cumulative_weight & 0xFFFF)) {
                        *category_out = (s8)category_index;
                        *item_out = (s8)item_index;
                        return selected_category;
                    }
                } else {
                    rarity = (scan_value >> 0xC) & 3;
                    category_scale_or_weight = 0x80;
                    if (rarity != 0) {
                        category_scale_or_weight = 0x55;
                        if (rarity != 1) {
                            category_scale_or_weight = 1;
                            if (rarity == (s32)table_base_or_mode) {
                                category_scale_or_weight = 0x20;
                            }
                        }
                    }
                    cumulative_weight += category_scale_or_weight;
                    if (random_weight < (u32)(cumulative_weight & 0xFFFF)) {
                        *category_out = (s8)category_index;
                        *item_out = (s8)item_index;
                        return selected_category;
                    }
                }
                category_scale_or_weight = category_index * 4;
                scan_value = item_category_table[((category_scale_or_weight + category_index) * 4) + 2];
            }
        } else {
            category_scale_or_weight = category_index * 4;
            scan_value = item_category_table[((category_scale_or_weight + category_index) * 4) + 2];
        }
        item_index += 1;
        item_offset += 0x14;
        if (item_index < scan_value) {
            goto loop_6;
        }
    }
    *category_out = 0;
    *item_out = 0;
    return 0;
}

/* Spends a floor-dependent random budget on category-14 drops at unoccupied item tiles. */
void generate_random_dungeon_item_drops(void)
{
    u8 x;
    u8 y;
    register s32 budget;
    s32 index;
    s32 decrement;
    s32 amount;
    s32 flag;
    s32 type;
    s32 cell_index;
    s32 scan_x;
    s32 scan_y;
    s32 scaled;
    u8 *mode_page;
    s32 entry_state;
    DungeonItemEntry *entry;
    floor_spawns_isolated_8028BC54_DungeonCell *cell;
    DungeonItemEntry *entry_scan;
    floor_spawns_isolated_8028BC54_DungeonCell *cell_scan;
    DungeonItemEntry *entry_base;
    u8 *cell_page;
    floor_spawns_isolated_8028BC54_DungeonCell *cell_base = 0;

    mode_page = D_80010000;
    if (*(s32 *)(mode_page + 0x2090) == 2) {
        mode_page = (u8 *)(*(s16 *)current_dungeon_floor);
        scaled = ((s32)mode_page) * 25;
        budget = scaled << 3;
    } else {
        budget = 75;
        if ((*(s16 *)current_dungeon_floor) >= 12) {
            budget = 700;
            if ((*(s16 *)current_dungeon_floor) < 22) {
                budget = 200;
            }
        }
    }

    if (generate_random_value() & 1) {
        budget += (u16)random_dungeon_range_16(0, (budget / 2) & 0xFFFF);
    } else {
        budget -= (u16)random_dungeon_range_16(0, (budget / 2) & 0xFFFF);
    }

    if (budget >= 0) {
        entry_base = (DungeonItemEntry *)((u8 *)dungeon_ground_items);
        cell_page = (u8 *)0x800E0000;
        do {
        cell_index = (s16)find_first_empty_floor_item_slot();
        if (cell_index < 0) {
            return;
        }

        if (budget >= 301) {
            decrement = (u16)random_dungeon_range_16(160, 240);
            flag = 1;
            type = ITEM_GOLD_COIN;
            amount = (decrement / 10 + (decrement >> 31)) & 0x3FFFFFFF;
        } else if (budget >= 151) {
            decrement = (u16)random_dungeon_range_16(80, 120);
            amount = decrement;
            flag = 0;
            type = ITEM_SILVER_COIN;
        } else {
            decrement = (u16)random_dungeon_range_16(16, 24);
            amount = decrement;
            flag = 0;
            type = ITEM_COPPER_COIN;
        }

        do {
        } while ((select_dungeon_spawn_tile(&x, &y) << 16) < 0);

        scan_x = x;
        scan_y = y;
        for (index = 0, cell_scan = (floor_spawns_isolated_8028BC54_DungeonCell *)dungeon_ground_item_positions, entry_scan = entry_base;
             index < 64;
             cell_scan++, index++, entry_scan++) {
            if (!(entry_scan->kind == ITEM_KIND_NONE || cell_scan->x != scan_x || cell_scan->y != scan_y)) {
                break;
            }
        }

        if (index == 64) {
            entry = (DungeonItemEntry *)((cell_index << 2) + (unsigned long)entry_base);
            cell_base = (floor_spawns_isolated_8028BC54_DungeonCell *)(cell_page + 0x36C8);
            entry->unk_00 = type;
            entry->kind = ITEM_KIND_COIN;
            entry->unk_03 = flag;
            entry->unk_02 = amount;
            cell = (floor_spawns_isolated_8028BC54_DungeonCell *)((cell_index * 12) +
                                            (unsigned long)cell_base);
            cell->x = x;
            cell->y = y;
            cell->height = get_surface_height_at_coordinates((x << 6) | 32, (y << 6) | 32);
            cell->flag7 = 0;
            cycle_map_cell_flags(x, y, TILE_HAS_ITEM);
            cell->object = get_item_category_value((void *)entry);
        }

        budget -= decrement;
        } while (budget >= 0);
    }
    return;
}

/* Restores recorded monsters, then places and initializes saved or randomly selected floor traps. */
void restore_spawns_and_place_floor_traps(void) {
    u8 x;
    u8 y;
    floor_spawns_isolated_8028BF0C_S_8001EF0C_1 *floor_config;
    floor_spawns_isolated_8028BF0C_SpawnPosition *position;
    floor_spawns_isolated_8028BF0C_SpawnMeta *meta;
    s32 *limits;
    u32 *initial;
    s32 slot;
    s32 spawn_limit;
    s32 trap_budget;
    s32 trap_cost;
    s32 value;
    void *availability;
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
    initial = level_experience_table;
    limits = (s32 *)(initial + 1);
    meta = ((floor_spawns_isolated_8028BF0C_SpawnMeta *)floor_objects);
    position = dungeon_floor_object_positions;
    do {
        if (meta[slot].state == 0x13) {
            existing_type = meta[slot].type;
            availability = find_or_retain_sprite_resource_slot(existing_type, 1);
            if (availability != 0) {
                object = load_monster_code_module(existing_type, availability, 1)
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
                        loop_limits = entity_level_thresholds;
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

    floor_config = (floor_spawns_isolated_8028BF0C_S_8001EF0C_1 *)floor_generation_state;
    if (floor_config->unk_06 == 1) {
        spawn_limit = (generate_random_value() & 3) + 4;
    } else {
        spawn_limit = floor_config->unk_06 / 2 + (generate_random_value() & 3);
    }
    if (spawn_limit >= 0x21) {
        spawn_limit = 0x20;
    }

    value = generate_random_value();
    slot = 0;
    trap_state = 0x15;
    position = dungeon_floor_object_positions;
    trap_budget = ((s16 *)current_dungeon_floor)[0] / 2 + (value & 0x3F);
    meta = ((floor_spawns_isolated_8028BF0C_SpawnMeta *)floor_objects);

    for (; slot < 0x20; slot++) {
        if (meta[slot].state == trap_state) {
            x = position[slot].x;
            y = position[slot].y;
            trap_type = meta[slot].type;
            spawn_variant = meta[slot].unk2;
            spawn_marker = meta[slot].unk3;
            spawn_height = -0x400;
        } else {
            if ((floor_loaded_content_flags[0] & 8) || slot >= spawn_limit) continue;
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
            if (!((dungeon_floor_flags & 0x20000000) || ((u8)(trap_type - 0xF) >= 2))) continue;
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
        cycle_map_cell_flags(x, y, TILE_HAS_OBJECT);
        {
            u8 *lookup_base = 0;
            s32 table_index;

            table_index = trap_type;
            lookup_base = floor_object_sprite_sources;
            value = *(s32 *)(lookup_base + (table_index << 2));
        }
        if (value < 0) {
            select_record_entry_and_value(&position[slot], value, 0);
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

/* Clears the 32 words of floor_objects in reverse order. */
void clear_dungeon_object_entries(void) {
    s32 entry_index;

    for (entry_index = 0x1F; entry_index >= 0; entry_index--) {
        ((int *)floor_objects)[entry_index] = 0;
    }
}

/* Creates a label sprite at the requested screen position with a normal or alternate tint. */
void create_tinted_dungeon_object(s16 x, s16 y, s16 tinted, s32 render_param)
{
    u16 flags;
    SpriteFrameState *render_state;
    ObjectNodeHeader *object;
    s16 *position;
    s16 *object_data;

    object = allocate_flagged_object_node(2);
    if (object != NULL) {
        object->update_callback = D_800A5AF0;
        register_node(object, linked_sprite_renderer_address);
        position = (s16 *)object->position;
        position[1] = x + 0x280;
        position[3] = y;
        position[5] = 1;
        render_state = object->sprite;
        render_state->scale_x = 0x2000;
        render_state->scale_y = 0x1000;
        render_state->source = render_param;
        if (tinted != 0) {
            render_state->color.word = 0x202080;
        } else {
            render_state->color.word = 0x808080;
        }
        flags = render_state->flags;
        render_state->tpage_abr = 0x20;
        object_data = (((void *)object) + 0x20);
        render_state->flags = flags | 0xC;
        object_data[3] = 0x18;
        object_data[4] = x;
    }
}

/* Creates the floor label and number sprites, or the special label used on floor 40. */
void draw_dungeon_value_and_label(void)
{
    u8 digits[3];
    u8 *digit_ptr;
    void *special_label;
    s32 draw_mode;
    s16 draw_x;
    s32 draw_y_fixed;
    s32 blank_code;
    u8 digit;
    special_label = 0;
    if (*(s32 *)0x80012090 != 2) {
        if ((*(s16 *)current_dungeon_floor) == 0x28) {
            special_label = D_80077E00;
        }
        draw_mode = 0;
    } else {
        draw_mode = 1;
    }

    if (special_label != 0) {
        create_tinted_dungeon_object(0xAA, 0x78, 0, special_label);
        return;
    }

    create_tinted_dungeon_object(0xAA, 0x78, draw_mode, D_80077DE8);
    /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_8028C450). */
    do {
        digit_ptr = digits;
    } while (0);
    func_8004E634((*(s16 *)current_dungeon_floor), digit_ptr);

    draw_x = 0xC8;
    if (digits[1] == 0) {
        draw_x = 0xDA;
    }

    if (digits[0] != 0) {
        blank_code = 0x20;
        draw_y_fixed = 0x780000;
        do {
            digit = *digit_ptr;
            if (digit != blank_code) {
                create_tinted_dungeon_object(draw_x, draw_y_fixed >> 16, draw_mode, D_8001F5B4[digit]);
            }
            digit_ptr++;
            draw_x += 0x12;
        } while (*digit_ptr != 0);
    }
}
