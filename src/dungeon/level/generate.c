#include "shared/monster_ids.h"
#include "dungeon/level/tile_flags.h"
/* Floor layout loading, random room and corridor generation, and special room placement. */
#include "shared/dungeon_status.h"
#include "dungeon/level/generate.h"
#include "shared/item_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/state.h"
#include "dungeon/effect.h"
#include "dungeon/effect/screen.h"
#include "dungeon/level.h"
#include "dungeon/system.h"

/* Clears all three halfwords in each of the 4,096 generation cells. */
void clear_generation_cell_grid(void) {
    s8 *entry_start;
    s8 *entry_tail;
    s32 entries_left;

    entry_start = ((u8 *)generation_cells);
    entries_left = 0x1000;
    entry_tail = entry_start + 2;
    do {
        entries_left -= 1;
        ((floor_generate_isolated_8028444C_S_8001744C_0 *)entry_start)->unk_00 = 0;
        ((floor_generate_isolated_8028444C_S_8001744C_1 *)entry_tail)->unk_02 = 0;
        ((floor_generate_isolated_8028444C_S_8001744C_1 *)entry_tail)->unk_00 = 0;
        entry_tail += 6;
        entry_start += 6;
    } while (entries_left > 0);
}

/* Keeps only the requested flag bits in each generation cell within the rectangle. */
void mask_generation_cell_rect(s16 start_x, s16 start_y, s16 rect_width, s16 rect_height, u16 mask)
{
    s32 x;
    s32 y;
    MapGrid *config;
    floor_generate_isolated_80284480_DungeonCell *cells;

    config = &g_game_work.map;
    cells = ((floor_generate_isolated_80284480_DungeonCell *)generation_cells);
    for (y = start_y; y < start_y + rect_height; y++) {
        for (x = start_x; x < start_x + rect_width; x++) {
            cells[x + (y << config->shiftX)].field_4 &= mask;
        }
    }
}

/* Calls mask_generation_cell_rect with 0, 0, 0x40, 0x40, 0. */
void clear_generation_cell_masks(void) {
    mask_generation_cell_rect(0, 0, 0x40, 0x40, 0);
}

/* Clears the word at offset 0x0C in each of the 36 dungeon-room records. */
void clear_thirty_six_table_fields(void) {
    s8 *entry;
    s32 remaining;

    entry = dungeon_rooms;
    remaining = 0x24;
    do {
        ((floor_generate_isolated_80284560_S_80017560_0 *)entry)->unk_0C = 0;
        remaining -= 1;
        entry += 0x14;
    } while (remaining > 0);
}

/* Returns the first nonzero generation mark in the rectangle, or -1 for invalid bounds. */
s16 find_first_nonzero_rectangle_field(s16 start_x, s16 start_y, s16 width, s16 height) {
    MapGrid *config;
    s32 shifted_x;
    s32 shifted_width;
    s32 row;
    s32 rows_left;

    row = start_y;
    if (row <= 0) {
        return -1;
    }
    shifted_x = start_x << 16;
    if ((shifted_x >> 16) <= 0) {
        goto ret_err;
    }
    config = &g_game_work.map;
    if (row + height >= (1 << config->shiftY)) {
        return -1;
    }
    shifted_width = width << 16;
    if ((shifted_x >> 16) + (shifted_width >> 16) >= (1 << config->shiftX)) {
ret_err:
        return -1;
    }
    rows_left = height;
    while (rows_left > 0) {
        s32 cols_left;
        s32 x;

        cols_left = shifted_width >> 16;
        x = shifted_x >> 16;
        while (cols_left > 0) {
            floor_generate_isolated_80284584_DungeonCell *cell;

            cell = &((floor_generate_isolated_80284584_DungeonCell *)generation_cells)[(row << config->shiftX) + x];
            if (cell->field_4 != 0) {
                return (s16)cell->field_4;
            }
            cols_left -= 1;
            x += 1;
        }
        rows_left -= 1;
        row += 1;
    }
    return 0;
}

/* Writes the given mark into every generation cell in the rectangle. */
void fill_generation_cell_marks(s16 start_x, s16 y, s16 width, s32 height, u16 fill_value) {
    s16 rows_left;
    s32 span_left;
    s32 width_shifted;
    s32 start_x_shifted;
    s32 x;
    s32 row_y;
    MapGrid *grid_settings;
    s32 cell_index;
    u16 *cell;

    rows_left = height;
    grid_settings = &g_game_work.map;
    if ((height << 16) > 0) {
        width_shifted = width << 16;
        start_x_shifted = start_x << 16;
        do {
            span_left = width_shifted >> 16;
            x = start_x_shifted >> 16;
            if (span_left > 0) {
                row_y = y;
                do {
                    span_left--;
                    cell_index = grid_settings->shiftX;
                    cell_index = row_y << cell_index;
                    cell_index += x;
                    x++;
                    cell = (u16 *)(((u8 *)generation_cells) + cell_index * 6);
                    cell[2] = fill_value;
                } while (span_left > 0);
            }
            rows_left--;
            y++;
        } while (rows_left > 0);
    }
}


/* Packs active room records together, clears unused slots, and updates the room count. */
void compact_generation_regions(void) {
    s8 *read_entry;
    s8 *write_entry;
    s32 entry_count;
    s32 entry_index;

    entry_index = 0;
    entry_count = 0;
    read_entry = (s8 *)dungeon_rooms;
    write_entry = (s8 *)dungeon_rooms;
    do {
        if (*(s16 *)(read_entry + 0xA) != 0) {
            if (entry_index != entry_count) {
                *(floor_generate_isolated_802846EC_DungeonEntry *)write_entry = *(floor_generate_isolated_802846EC_DungeonEntry *)read_entry;
            }
            write_entry += 0x14;
            entry_count += 1;
        }
        entry_index += 1;
        read_entry += 0x14;
    } while (entry_index < 0x24);

    entry_index = entry_count;
    if (entry_count < 0x24) {
        do {
            dungeon_rooms[entry_index].active = 0;
            dungeon_rooms[entry_index].entry_count = 0;
            dungeon_rooms[entry_index].entries = 0;
        } while (++entry_index < 0x24);
    }
    ((s16 *)dungeon_room_count)[0] = entry_count;
}

void clear_generation_region_entries(void) {
    s32 i;

    for (i = 0x23; i >= 0; i--) {
        dungeon_rooms[i].active = 0;
        dungeon_rooms[i].entry_count = 0;
        dungeon_rooms[i].entries = 0;
    }
}

/* Appends coordinates and a value to an active room's cell list. */
void append_generation_region_entry(s16 row_index, s16 first_byte, s16 second_byte, s16 value) {
    s32 row_offset;
    u16 entry_count;
    void *rows_base;
    void *entries_base;
    floor_generate_isolated_802847D8_S_800177D8_0 *row;
    floor_generate_isolated_802847D8_S_800177D8_1 *entry;

    rows_base = (void *)dungeon_rooms;
    row = (row_index * 0x14) + rows_base;
    if (row->unk_0A != 0) {
        row_offset = row_index << 6;
        entries_base = (void *)generation_region_cell_entries;
        entry_count = row->unk_0E;
        row->unk_10 = row_offset + entries_base;
        entry = ((s32)(entry_count << 0x10) >> 0xE) + row_offset + entries_base;
        row->unk_0E = (u16)(entry_count + 1);
        entry->unk_02 = value;
        entry->unk_00 = first_byte;
        entry->unk_01 = second_byte;
    }
}

/* Places up to four elevator markers on free spawn tiles and lowers their terrain by 32. */
void place_random_floor_elevators(void) {
    s32 state;
    u8 x;
    u8 y;
    MapGrid *config;
    floor_generate_isolated_8028484C_MapCell *map;
    s32 spawn_count;
    s32 slot_index;
    u8 *meta_base;
    DungeonFloorMarker *entries;

    {
        u8 *state_page;
        state_page = (u8 *)0x80010000;
        state = *(s32 *)(state_page + 0x2090);
    }
    config = &g_game_work.map;
    map = *(floor_generate_isolated_8028484C_MapCell **)((u8 *)(&g_game_work.map));

    if ((state == 2) || ((*(s16 *)current_dungeon_floor) != 0x28)) {
        spawn_count = 0;
        meta_base = ((u8 *)dungeon_ground_items);

        do {
retry:
        do {
        } while ((s16)select_dungeon_spawn_tile(&x, &y) < 0);

        {
            u8 *meta;
            u8 *position;

            slot_index = 0;
            position = ((u8 *)dungeon_ground_item_positions);
            meta = meta_base;

            do {
                if ((meta[1] != 0) && (position[0] == x) &&
                    (position[1] == y)) {
                    goto retry;
                }
                position += 12;
                slot_index++;
                meta += 4;
            } while (slot_index < 0x40);
        }

        {
            s32 position_page;
            u8 *meta;
            u8 *position;

            slot_index = 0;
            position = ((u8 *)dungeon_floor_object_positions);
            meta = (u8 *)((u8 *)floor_objects);

            do {
                position_page = (meta + slot_index * 4)[1];
                if ((position_page != 0) && ((position + slot_index * 24)[6] == x) &&
                    ((position + slot_index * 24)[7] == y)) {
                    goto retry;
                }
                slot_index++;
            } while (slot_index < 0x20);
        }

        entries = dungeon_floor_marker_entries;
        {
            DungeonFloorMarker *entry = &entries[spawn_count];
            s32 spawn_x;
            s32 spawn_y;
            s32 cell_offset;
            s32 row_offset;
            s32 update_row_shift;
            s32 copy_row_shift;
            s32 flags_row_shift;
            s32 cell_index;
            floor_generate_isolated_8028484C_MapCell *spawn_cell;
            s32 update_size;

            spawn_x = x;
            spawn_y = y;
            (*(s16 *)((u8 *)entry + 0)) = 2;
            (*(s16 *)((u8 *)entry + 2)) = spawn_x;
            (*(s16 *)((u8 *)entry + 4)) = spawn_y;

            row_offset = y;
            update_row_shift = config->shiftX;
            cell_offset = x;
            cell_index = cell_offset + (row_offset << update_row_shift);
            map[cell_index].value -= 0x20;

            copy_row_shift = config->shiftX;
            entry->height = map[cell_offset + (row_offset << copy_row_shift)].value;

            flags_row_shift = config->shiftX;
            row_offset <<= flags_row_shift;
            cell_offset += row_offset;
            spawn_cell = (floor_generate_isolated_8028484C_MapCell *)(cell_offset * 6 + (long)map);
            update_size = 0x20;
            spawn_cell->flags = 1;
            cycle_map_cell_flags(spawn_x, spawn_y, update_size);
        }

        if ((generate_random_value() & 0x3F) != 0) {
            break;
        }
        spawn_count++;
        } while (spawn_count < 4);

        spawn_count++;
        while (spawn_count < 4) {
            entries[spawn_count].kind = 0;
            spawn_count++;
        }
    }
}

/* Writes blocked border tiles around the generation grid. */
void initialize_grid_border_cells(void)
{
    s32 edge_index;
    floor_generate_isolated_80284A9C_Cell *cell;
    MapGrid *grid_config = &g_game_work.map;

    edge_index = 0;
    if ((1 << grid_config->shiftY) > 0) {
        s32 border_type = 3;
        s32 border_attr = 0x400;
        s32 step = 1;

        do {
            cell = &((floor_generate_isolated_80284A9C_Cell *)generation_cells)[edge_index << grid_config->shiftX];
            cell->field_0 = border_type;
            cell->field_2 = border_attr;
            cell->field_4 |= 0x8001;

            cell = &((floor_generate_isolated_80284A9C_Cell *)generation_cells)[((step + edge_index) << grid_config->shiftX) - 1];
            cell->field_0 = border_type;
            cell->field_2 = border_attr;
            cell->field_4 |= 0x8001;
        } while (++edge_index < (step << grid_config->shiftY));
    }

    for (edge_index = 0; edge_index < (1 << grid_config->shiftY); edge_index++) {
        cell = &((floor_generate_isolated_80284A9C_Cell *)generation_cells)[edge_index];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;

        cell = &((floor_generate_isolated_80284A9C_Cell *)generation_cells)[(((1 << grid_config->shiftY) - 1) << grid_config->shiftX) + edge_index - 1];
        cell->field_0 = 3;
        cell->field_2 = 0x400;
        cell->field_4 |= 0x8001;
    }
}

/* Marks reachable room tiles, returning 0 when traversal cannot cover the eligible cells. */
s32 mark_path_through_neighboring_tiles(s16 region_id) {
    s16 *dx = dir_step_x;
    s16 *dy = dir_step_y;
    s16 x;
    s16 y;
    floor_generate_isolated_80284BEC_S_80017BEC_M *map;
    floor_generate_isolated_80284BEC_S_80017BEC_T *tiles;
    s16 tile_id;
    s16 steps;
    s32 direction;
    s16 next_direction;
    s32 open_count;
    u16 flags;
    s32 idx;

    tiles = (*(floor_generate_isolated_80284BEC_S_80017BEC_M *)scene_geometry).tiles;
    map = &(*(floor_generate_isolated_80284BEC_S_80017BEC_M *)scene_geometry);
    tile_id = find_highest_eligible_sample(region_id, &x, &y, 0);
    if (tile_id >= 0x200) {
        return 0;
    }
    idx = x + (y << map->unk_14);
    tiles[idx].unk_04 |= 0x100;
    steps = count_unblocked_cells_in_generation_region(region_id);
    for (;;) {
        next_direction = -1;
        open_count = 0;
        for (direction = 7; direction >= 0; direction--) {
            if ((s16)classify_directional_movement(x, y, tile_id, (s16)direction) != 0) {
                floor_generate_isolated_80284BEC_S_80017BEC_T *tile;
                idx = (x + dx[direction]) + ((y + dy[direction]) << map->unk_14);
                tile = (floor_generate_isolated_80284BEC_S_80017BEC_T *)((idx * 6) + (long)tiles);
                flags = tile->unk_04;
                if (!(flags & 0x100)) {
                    tile->unk_04 = flags | 0x200;
                    next_direction = direction;
                }
                open_count++;
            }
        }
        if (open_count == 0) {
            return 0;
        }
        if (next_direction >= 0) {
            floor_generate_isolated_80284BEC_S_80017BEC_T *tile;
            x += dx[next_direction];
            y += dy[next_direction];
            idx = x + (y << map->unk_14);
            tile = (floor_generate_isolated_80284BEC_S_80017BEC_T *)((idx * 6) + (long)tiles);
            steps--;
            tile->unk_04 |= 0x100;
            if (steps <= 0) {
                break;
            }
            tile_id = sample_terrain_surface_height(((x << 6) + 0x20) & 0xFFE0, ((y << 6) + 0x20) & 0xFFE0, -0x400);
        } else {
            tile_id = find_first_qualifying_cell(region_id, &x, &y, 1);
            if (tile_id >= 0x200) {
                return 0;
            }
            idx = x + (y << map->unk_14);
            tiles[idx].unk_04 |= 0x100;
            if (--steps <= 0) {
                break;
            }
        }
    }
    return 1;
}

/* Counts room cells whose flags have none of the bits in 0x8500 set. */
s16 count_unblocked_cells_in_generation_region(s16 entry_index) {
    s16 count = 0;
    u8 *entry_base = (u8 *)dungeon_rooms;
    floor_generate_isolated_80284EBC_DungeonEntry *region = (floor_generate_isolated_80284EBC_DungeonEntry *)(entry_base + (entry_index * 20));
    MapGrid *state = &g_game_work.map;
    s16 height = region->height;
    u16 y = region->y;
    s16 rows_left = height;

    if (height > 0) {
        floor_generate_isolated_80284EBC_DungeonEntry *entry = region;

        while (rows_left > 0) {
            floor_generate_isolated_80284EBC_DungeonCell *cell = (floor_generate_isolated_80284EBC_DungeonCell *)((u8 *)((floor_generate_isolated_80284EBC_DungeonCell *)state->cells) + (((s16)y << state->shiftX) * 6)
                + (entry->x * 6));
            s16 cols_left = entry->width;

            while (cols_left > 0) {
                if (!(cell->flags & 0x8500)) {
                    count++;
                }
                cell++;
                cols_left--;
            }
            y++;
            rows_left--;
        }
    }
    return count;
}

/* Finds the highest eligible surface in a room, returning 0x200 when none is found. */
s16 find_highest_eligible_sample(s16 rect_index, s16 *out_x, s16 *out_y, s16 check_flags)
{
    s16 best_value;
    s16 rows_left;
    s16 cols_left;
    s16 tile_y;
    s16 tile_x;
    s16 tile_value;
    s32 row_index;
    u16 flags;
    s32 tile_center_y;
    floor_generate_isolated_80284F88_DungeonCell *cells;
    MapGrid *state;

    best_value = -0x200;
    rows_left = dungeon_rooms[rect_index].h;
    tile_y = dungeon_rooms[rect_index].y;
    state = &g_game_work.map;
    cells = ((floor_generate_isolated_80284F88_DungeonCell *)state->cells);
    if (rows_left > 0) {
        do {
            cols_left = dungeon_rooms[rect_index].w;
            tile_x = dungeon_rooms[rect_index].x;
            if (cols_left > 0) {
                row_index = (s16)tile_y;
                tile_center_y = (row_index << 6) + 0x20;
                do {
                    flags = cells[(s16)tile_x
                        + (row_index << state->shiftX)].flags;
                    if (!(flags & 0x8400)
                        && ((check_flags == 0)
                            || ((flags & 0x300) == 0x200))) {
                        tile_value = sample_terrain_surface_height(
                            (((s16)tile_x << 6) + 0x20) & 0xFFE0,
                            tile_center_y & 0xFFFF,
                            -0x400);
                        if (tile_value < 0x200) {
                            if (best_value < tile_value) {
                                *out_x = tile_x;
                                best_value = tile_value;
                                *out_y = tile_y;
                            }
                        }
                    }
                    cols_left--;
                    tile_x++;
                } while ((cols_left << 16) > 0);
            }
            rows_left--;
            tile_y++;
        } while ((rows_left << 16) > 0);
    }
    if (best_value == -0x200) {
        best_value = 0x200;
    }
    return best_value;
}


/* Returns the first unvisited frontier tile's surface height and coordinates, or 0x200. */
s16 find_first_qualifying_cell(s16 record_id, s16 *out_x, s16 *out_y, s32 search_mode)
{
    s16 rows_left;
    s16 cols_left;
    u16 y;
    s16 x;
    s16 cell_result;
    s32 row;
    u16 flags;
    s32 center_y;
    floor_generate_isolated_8028516C_DungeonCell *cell;
    MapGrid *state;

    rows_left = dungeon_rooms[record_id].h;
    y = dungeon_rooms[record_id].y;
    state = &g_game_work.map;
    if (rows_left > 0) {
        do {
            row = (s16)y;
            x = dungeon_rooms[record_id].x;
            cols_left = dungeon_rooms[record_id].w;
            cell = (floor_generate_isolated_8028516C_DungeonCell *)state->cells + (row << state->shiftX) + x;
            if (cols_left > 0) {
                center_y = (row << 6) + 0x20;
                do {
                    flags = cell->flags;
                    if (!(flags & 0x8400)) {
                        if ((flags & 0x300) == 0x200) {
                            cell_result = sample_terrain_surface_height((((s16)x << 6) + 0x20) & 0xFFE0, center_y & 0xFFFF, -0x400);
                            if (cell_result < 0x200) {
                                *out_x = x;
                                *out_y = y;
                                return cell_result;
                            }
                        }
                    }
                    x++;
                    cols_left--;
                    cell++;
                } while ((cols_left << 16) > 0);
            }
            rows_left--;
            y++;
        } while ((rows_left << 16) > 0);
    }
    return 0x200;
}

/* Checks a neighboring tile and returns 2 for level or downhill movement, 1 for a small climb, or 0. */
s32 classify_directional_movement(s16 input_x, s16 input_y, s32 current_height, s16 direction)
{
    u16 tile_flags;
    s16 tile_x;
    s16 tile_y;
    s16 probe_height;
    s16 target_height;
    s16 next_x;
    s16 next_y;

    probe_height = current_height - 0x20;
    tile_x = input_x;
    tile_y = input_y;
    if ((check_diagonal_side_height(direction & 0xFFFF, tile_x, tile_y, probe_height) << 16) == 0) {
        return 0;
    }

    if ((get_offset_map_cell_value_and_flags(tile_x, tile_y, direction, &tile_flags) << 16) == 0) {
        return 0;
    }

    next_x = input_x + dir_step_x[direction];
    next_y = input_y + dir_step_y[direction];
    if (tile_flags & 0x8400) {
        return 0;
    }

    target_height = sample_terrain_surface_height(
        ((next_x << 6) + 0x20) & 0xFFE0,
        ((next_y << 6) + 0x20) & 0xFFE0,
        probe_height);
    if (target_height < 0x200) {
        if ((s16)current_height >= target_height) {
            return 2;
        }
        if ((target_height - (s16)current_height) < 0x21) {
            return 1;
        }
    }
    return 0;
}


/* Loads a fixed floor's rooms, elevators, items, objects, and compressed terrain from CD. */
void load_dungeon_layout(s16 layout_number)
{
    MapGrid *cfg;
    floor_generate_isolated_80285464_MapCell *map;
    floor_generate_isolated_80285464_RecB *placed_record;
    u8 *data;
    u8 *data_2;
    u16 *room_header;
    s32 entry_index;
    s16 layout_index;
    s32 x_or_marker;
    void *layout_id;
    s32 map_value;
    u16 tile_value;
    u16 shift_y;

    layout_index = layout_number - 1;
    data_2 = ((SpriteFrameState *)gpu_scratch_buffer_base)->unk_00;
    (*(u8 **)gpu_scratch_write_pointer) = data_2;
    layout_id = floor_layout_resource_descriptors[layout_index];
    cfg = &g_game_work.map;
    map = ((floor_generate_isolated_80285464_MapCell *)cfg->cells);
    Control_CD(6, layout_id, 0);
    drain_cd_command_queue();
    entry_index = 0;

    room_header = (u16 *)(data_2 + 4);
    cfg->shiftX = ((u16 *)data_2)[0];
    cfg->maskX = (1 << cfg->shiftX) - 1;
    shift_y = ((u16 *)data_2)[1];
    cfg->spanX = 64 << cfg->shiftX;
    cfg->shiftY = shift_y;
    cfg->maskY = (1 << cfg->shiftY) - 1;
    cfg->spanY = 64 << cfg->shiftY;

    while (room_header[2] != 0) {
        ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].active = 1;
        ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].x = room_header[0];
        ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].y = room_header[1];
        ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].w = room_header[2];
        ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].h = room_header[3];
        ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].count = 0;
        room_header += 4;
        data = (u8 *)room_header;
        while (*data != 0) {
            ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].tiles = &generation_region_cell_entries[entry_index << 6];
            floor_generate_isolated_80285464_ROOM_CELL(entry_index, ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].count).a = *data++;
            floor_generate_isolated_80285464_ROOM_CELL(entry_index, ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].count).b = *data++;
            floor_generate_isolated_80285464_ROOM_CELL(entry_index, ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].count).c = *data;
            data += 2;
            ((floor_generate_isolated_80285464_Room *)dungeon_rooms)[entry_index].count++;
        }
        entry_index++;
        data += 2;
        room_header = (u16 *)data;
    }
    room_header += 4;
    data = (u8 *)room_header;
    (*(s16 *)dungeon_room_count) = entry_index;
    entry_index = 0;
    while (*data != 0) {
        dungeon_floor_marker_entries[entry_index].kind = data[2] + 2;
        dungeon_floor_marker_entries[entry_index].x = data[0];
        dungeon_floor_marker_entries[entry_index].y = data[1];
        tile_value = map[data[0] + (data[1] << cfg->shiftX)].value - 32;
        map[data[0] + (data[1] << cfg->shiftX)].value = tile_value;
        dungeon_floor_marker_entries[entry_index].height = tile_value;
        if (dungeon_floor_marker_entries[entry_index].kind == 2) {
            map[data[0] + (data[1] << cfg->shiftX)].kind = 1;
        }
        cycle_map_cell_flags(data[0], data[1], TILE_HAS_OBJECT);
        entry_index++;
        data += 4;
    }
    if (try_add_second_tower_entry(entry_index) != 0) {
        entry_index++;
    }
    floor_layout_loaded = 1;
    entry_index++;
    while (entry_index < 4) {
        dungeon_floor_marker_entries[entry_index].kind = 0;
        entry_index++;
    }

    data += 2;
    entry_index = 0;
    while ((x_or_marker = *data) != 0) {
        if (x_or_marker == 99) {
            floor_loaded_content_flags |= 2;
            data += 6;
            break;
        }
        data++;
        ((floor_generate_isolated_80285464_RecB *)dungeon_ground_item_positions)[entry_index].f0 = x_or_marker;
        ((floor_generate_isolated_80285464_RecB *)dungeon_ground_item_positions)[entry_index].f1 = *data++;
        dungeon_ground_items[entry_index].unk_00 = *data++;
        dungeon_ground_items[entry_index].kind = *data++;
        dungeon_ground_items[entry_index].unk_03 = *data++;
        dungeon_ground_items[entry_index].unk_02 = *data++;
        ((floor_generate_isolated_80285464_RecB *)dungeon_ground_item_positions)[entry_index].f8 = get_item_category_value(&dungeon_ground_items[entry_index]);
        entry_index++;
    }
    while (entry_index < 64) {
        dungeon_ground_items[entry_index].kind = ITEM_KIND_NONE;
        dungeon_ground_items[entry_index].unk_00 = 0;
        entry_index++;
    }

    data += 2;
    entry_index = 0;
    while ((x_or_marker = *data) != 0) {
        if (x_or_marker == 99) {
            floor_loaded_content_flags |= 8;
            data += 6;
            break;
        }
        data++;
        ((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f6 = x_or_marker;
        ((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f7 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f0 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f1 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f3 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f2 = *data++;
        ((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f8 = floor_object_sprite_sources[((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f0];
        cycle_map_cell_flags(((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f6, ((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f7, TILE_HAS_OBJECT);
        entry_index++;
    }

    data += 2;
    while (*data != 0) {
        dungeon_floor_flags |= 0x10000000;
        ((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f6 = *data++;
        ((floor_generate_isolated_80285464_RecC *)dungeon_floor_object_positions)[entry_index].f7 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f0 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f1 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f3 = *data++;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f2 = *data++;
        entry_index++;
    }
    data += 2;
    while (entry_index < 32) {
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f1 = 0;
        ((floor_generate_isolated_80285464_RecD *)floor_objects)[entry_index].f0 = 0;
        entry_index++;
    }

    decompress_lz(data, ((u8 *)generation_cells));
    for (entry_index = 0; dungeon_ground_items[entry_index].kind != ITEM_KIND_NONE; entry_index++) {
        placed_record = &((floor_generate_isolated_80285464_RecB *)dungeon_ground_item_positions)[entry_index];
        map_value = get_surface_height_at_coordinates(placed_record->f0 << 6, placed_record->f1 << 6);
        placed_record->f4 = map_value;
        *(s16 *)&placed_record->f2 = map_value;
    }
}

/* Seeds floor generation, loads a fixed or random layout, and places elevators and border tiles. */
void setup_run_and_load_track(void) {
    floor_generate_isolated_80285A70_State13710 *state;
    floor_generate_isolated_80285A70_Page8001 *page1;
    floor_generate_isolated_80285A70_TrackRecord *track;
    s16 *clearp;
    s32 value;
    s32 track_no;
    s32 action;
    s32 i;
    {
        GameWork *xor_base;
        u16 entry_flags;

        state = (floor_generate_isolated_80285A70_State13710 *)0x80013710;
        entry_flags = state->flags;
        xor_base = &g_game_work;

        if (entry_flags & 2) {
            u32 r;
            u16 fl;

            restore_dungeon_random_seed(state->seed);
            r = generate_random_value();
            state->field8 = 0;
            state->fieldA = 0;
            state->field6 = 0;
            state->seed += r & 0xFFFF;
            (*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).seed = state->seed;
            fl = state->flags;
            (*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).level = ((floor_generate_isolated_80285A70_LevelPage *)0x80010000)->level;
            fl &= 0xFFFC;
            state->flags = fl;
            bind_view_triplet_source(((u8 *)(&view_reference_entity)));
            bzero((void *)0x80013720, 0x2000);
        } else if (entry_flags & 1) {
            state->field8 = 0;
            state->fieldA = 0;
            (*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).seed = state->seed;
            (*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).level = ((floor_generate_isolated_80285A70_LevelPage *)0x80010000)->level;
            bind_view_triplet_source(((u8 *)(&view_reference_entity)));
        } else {
            u32 hi;

            state->flags = 0;
            value = rand();
            hi = rand();
            state->field8 = 0;
            state->field6 = 0;
            state->field11 = 0;
            state->field10 = 0;
            state->seed = (*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).seed = (value | (hi << 16)) ^ xor_base->unk_004;
            bind_view_triplet_source(((u8 *)(&view_reference_entity)));
            bzero((void *)0x80013720, 0x2000);
        }
    }

    srand((*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).seed);
    restore_dungeon_random_seed((*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).seed);
    store_random_nibble();
    runtime_dispatch_state.flags16 = 0;
    floor_loaded_content_flags = 0;
    clear_dungeon_object_entries();
    clear_dungeon_cell_entries();

    i = 3;
    clearp = ((s16 *)dungeon_floor_marker_entries);
    clearp += 12;
    do {
        *clearp = 0;
        i--;
        clearp -= 4;
    } while (i >= 0);

    page1 = (floor_generate_isolated_80285A70_Page8001 *)0x80010000;
    if ((u32)page1->level >= 100U) {
        page1->level = 99;
    }

    track_no = setup_dungeon_floor_encounters();
    if (track_no != 0) {
        floor_generate_isolated_80285A70_TrackRecord *tracks;

        track_no--;
        clear_thirty_six_table_fields();
        tracks = floor_track_configuration_records;
        track = &tracks[track_no];
        create_default_state_object(track->track);
        file_load_com(floor_track_resource_descriptors[track->table_index]);
        runtime_load_packed_resource_chunks(track->kind, D_800F0000);
        clear_generation_cell_grid();
        clear_generation_region_entries();
        if (track->arg != 0) {
            load_dungeon_layout(track->arg);
        }
        if (track->special == 0) {
            ((floor_generate_isolated_80285A70_Page800E *)0x800E0000)->flags &= ~0x20000000;
        } else {
            run_indexed_callback_list(track->special - 1);
            ((floor_generate_isolated_80285A70_Page800E *)0x800E0000)->flags &= ~0x20000000;
        }
    } else {
        if (page1->mode != 2) {
            create_default_state_object(floor_generation_track_variant % 24 + 3);
            action = floor_variant_resource_descriptors[floor_generation_track_variant % 24];
        } else {
            s32 random_remainder;

            random_remainder = generate_random_value() & 0xFFFF;
            random_remainder %= 24;
            create_default_state_object((s16)(random_remainder + 3));
            action = floor_variant_resource_descriptors[random_remainder];
        }

        file_load_com(action);
        ((floor_generate_isolated_80285A70_Page800E *)0x800E0000)->flags |= 0x20000000;
        runtime_load_packed_resource_chunks(0x29, D_800F0000, (floor_generate_isolated_80285A70_Page800E *)0x800E0000);
        create_wrapped_texture_scroll(2);

        do {
            clear_generation_cell_grid();
            clear_generation_region_entries();
        } while ((generate_floor_layout() << 16) != 0 || (*(floor_generate_isolated_80285A70_SaveHead *)floor_generation_state).ready == 0);

    }
    apply_state_index_tile_masks();
    if (floor_layout_loaded == 0) {
        place_random_floor_elevators();
    }
    initialize_grid_border_cells();
}


/* Selects floor events and sound resources, loads spawn tables, and sets special encounter records. */
s32 setup_dungeon_floor_encounters(void)
{
    s32 floor_event;
    s32 skip_floor_setup;
    s32 state;
    s32 floor_group;
    s32 encounter_status;
    s16 *floor_data;
    s32 final_floor;
    s32 monster_id;
    s32 level;
    u8 *base;

    floor_event = 0;
    skip_floor_setup = 0;
    state = floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_022c;
    if (state == 1) {
        if (((s16 *)current_dungeon_floor)[0] < 2) {
            floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090 = state;
            convert_valid_entry_code_2_to_39();
        } else if (floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090 == state) {
            floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090 = 0;
        }
    }

    state = scene_mode_code[0];
    switch (state) {
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
        floor_event = 0;
        break;
    default:
        state = floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_2090;
        if (state == 0) {
            floor_group = (s16)(((s16 *)current_dungeon_floor)[0] / 5);
            if (((s16 *)current_dungeon_floor)[0] >= 0x28) {
                skip_floor_setup = 1;
                dungeon_floor_flags |= 0x10000000;
            }

            if (((s16 *)current_dungeon_floor)[0] == 0x28) {
                floor_event = 1;
                if (test_resident_bit(0xA2) != 0) {
                    floor_group = 7;
                } else {
                    floor_group = -1;
                    set_first_table_entry_active();
                }
                skip_floor_setup = 1;
            } else if (((s16 *)current_dungeon_floor)[0] < 2) {
                floor_event = (generate_random_value() & 3) + 3;
            } else if (((s16 *)current_dungeon_floor)[0] == 2 && floor_generate_isolated_80285E80_DUNGEON_GLOBALS->state_022c != 1) {
                floor_event = 2;
                dungeon_floor_flags |= 0x10000000;
            } else if (((s16 *)current_dungeon_floor)[0] == 0x1F && test_resident_bit(0x1389) == 0) {
                dungeon_floor_object_positions[6] = 1;
                dungeon_floor_object_positions[7] = 1;
                ((u8 *)floor_objects)[0] = MONSTER_BELDO;
                ((u8 *)floor_objects)[1] = 0x13;
                ((u8 *)floor_objects)[3] = 0;
                ((u8 *)floor_objects)[2] = 0x63;
                dungeon_floor_flags |= 0x10000000;
            }

            if (floor_group >= 0) {
                encounter_status = load_object_into_alternate_buffer((s16)(floor_group + 1), 1, 1);
                if (encounter_status == 0) {
                    scene_music_hold[0] = 0;
                }
                if (scene_music_hold[0] == 0) {
                    wait_until_sound_idle();
                    scene_music_hold[0] = 1;
                    SD_Call(0x200);
                    drain_audio_commands_and_service_channels();
                }
                if (encounter_status == 0) {
                    load_object_into_alternate_buffer(0, 1, 0);
                }
            } else {
                load_object_into_alternate_buffer(0, 1, 0);
                load_object_into_alternate_buffer(0x29, 1, 1);
                SD_Call(0x200);
                drain_audio_commands_and_service_channels();
                load_and_upload_sprite_resource(0x38);
            }

            if (skip_floor_setup == 0) {
                load_floor_spawn_tables(((s16 *)current_dungeon_floor)[0]);
            }
        } else {
            skip_floor_setup = 1;
            if (state == 1) {
                floor_event = 9;
                dungeon_floor_flags |= 0x10000000;
                load_object_into_alternate_buffer(1, 1, 1);
                SD_Call(0x200);
                drain_audio_commands_and_service_channels();
                load_object_into_alternate_buffer(0, 1, 0);
            } else if (state == 2) {
                s32 i_m;
                floor_group = generate_random_value() & 7;
                encounter_status = load_object_into_alternate_buffer(floor_group + 1, 1, 1);
                if (encounter_status == 0) {
                    wait_until_sound_idle();
                    SD_Call(0x200);
                    drain_audio_commands_and_service_channels();
                    load_object_into_alternate_buffer(0, 1, 0);
                }

                floor_data = (s16 *)((u8 *)floor_generation_state);
                if (floor_data[2] == 1) {
                    s32 i;
                    {

                        u8 *even_ids;
                        u8 *odd_ids;
                        DungeonGlobalStatus *ds;

                        monster_id = random_dungeon_range_16(MONSTER_DRAGON, MONSTER_MAXIMUM) & 0xFFFF;
                        level = floor_data[2] + (generate_random_value() & 1);
                        if (level >= 100) {
                            level = 99;
                        }
                        i = 0;
                        ds = &g_dungeon_status;
                        base = ((u8 (*)[8])floor_species_pool)[0];
                        even_ids = base;
                        odd_ids = even_ids + 1;
                        do {
                            (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i].value = monster_id;
                            (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i].level = level;
                            i++;
                            *odd_ids = monster_id;
                            *even_ids = monster_id;
                            even_ids += 2;
                            odd_ids += 2;
                        } while (i < 4);
                    }

                    {

                        u8 *even_ids;
                        u8 *odd_ids;
                        DungeonGlobalStatus *ds;

                        monster_id = random_dungeon_range_16(MONSTER_DRAGON, MONSTER_MAXIMUM) & 0xFFFF;
                        level = ((s16 *)current_dungeon_floor)[0] + (generate_random_value() & 1);
                        if (level >= 100) {
                            level = 99;
                        }
                        i = 0;
                        ds = &g_dungeon_status;
                        base = ((u8 (*)[8])floor_species_pool)[1];
                        even_ids = base;
                        odd_ids = even_ids + 1;
                        do {
                            (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i + 4].value = monster_id;
                            (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i + 4].level = level;
                            i++;
                            *odd_ids = monster_id;
                            *even_ids = monster_id;
                            even_ids += 2;
                            odd_ids += 2;
                        } while (i < 4);
                    }
                } else {
                    *(floor_generate_isolated_80285E80_Packed16_80285E80 *)*(unsigned char **)&g_dungeon_status.monster_spawn_table =
                        *(floor_generate_isolated_80285E80_Packed16_80285E80 *)(*(unsigned char **)&g_dungeon_status.monster_spawn_table + 0x10);
                    *(floor_generate_isolated_80285E80_Packed16_80285E80 *)((u8 (*)[8])floor_species_pool)[0] =
                        *(floor_generate_isolated_80285E80_Packed16_80285E80 *)((u8 (*)[8])floor_species_pool)[2];
                }

                {

                    s32 level_bonus;
                    u8 *even_ids;
                    u8 *odd_ids;
                    DungeonGlobalStatus *ds;

                    monster_id = random_dungeon_range_16(MONSTER_DRAGON, MONSTER_MAXIMUM) & 0xFFFF;
                    level_bonus = generate_random_value() & 1;
                    i_m = 0;
                    base = ((floor_generate_isolated_80285E80_DungeonState80285E80 *)&g_dungeon_status);
                    ds = base;
                    final_floor = (s32)((u8 (*)[8])floor_species_pool)[2];
                    even_ids = (u8 *)final_floor;
                    odd_ids = even_ids + 1;
                    final_floor = ((s16 *)current_dungeon_floor)[0];
                    level = final_floor + level_bonus;
                    do {
                        (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i_m + 8].value = monster_id;
                        (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i_m + 8].level = level;
                        i_m++;
                        *odd_ids = monster_id;
                        *even_ids = monster_id;
                        even_ids += 2;
                        odd_ids += 2;
                    } while (i_m < 4);
                }

                {

                    s32 level_bonus;
                    u8 *even_ids;
                    u8 *odd_ids;
                    DungeonGlobalStatus *ds;

                    monster_id = random_dungeon_range_16(MONSTER_DRAGON, MONSTER_MAXIMUM) & 0xFFFF;
                    level_bonus = generate_random_value() & 1;
                    i_m = 0;
                    ds = &g_dungeon_status;
                    final_floor = (s32)((u8 (*)[8])floor_species_pool)[3];
                    even_ids = (u8 *)final_floor;
                    odd_ids = even_ids + 1;
                    final_floor = ((s16 *)current_dungeon_floor)[0];
                    level = final_floor + level_bonus;
                    do {
                        (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i_m + 12].value = monster_id;
                        (*(floor_generate_isolated_80285E80_DungeonRecord80285E80 **)&ds->monster_spawn_table)[i_m + 12].level = level;
                        i_m++;
                        *odd_ids = monster_id;
                        *even_ids = monster_id;
                        even_ids += 2;
                        odd_ids += 2;
                    } while (i_m < 4);
                }
            }
        }
    }

    final_floor = ((s16 *)current_dungeon_floor)[0];
    floor_generate_isolated_80285E80_DUNGEON_GLOBALS->floor_0234 = final_floor;
    return floor_event;
}

/* Loads the floor's monster spawn tables and terrain resource variant from CD. */
void load_floor_spawn_tables(s16 resource_index)
{
    s32 load_result;
    u8 *resource_data;

    resource_data = (u8 *)&dungeon_resource_buffer;
    pack_tagged_resource_descriptor(1, resource_data, &load_result, resource_index + 0x3F5E);
    Control_CD(6, &load_result, 0);
    drain_cd_command_queue();
    *(floor_generate_isolated_802864C4_Copy32 *)*(unsigned char **)&g_dungeon_status.monster_spawn_table = dungeon_resource_buffer;
    (*(floor_generate_isolated_802864C4_Copy32 *)floor_species_pool) = *(floor_generate_isolated_802864C4_Copy32 *)(resource_data + 0x20);
    floor_generation_track_variant = resource_data[0x40];
}

/*
 * Replaces code 2 with 0x39 in the indexed four-byte entry at 0x800121E8 when the saved index is
 * nonnegative.
 */
void convert_valid_entry_code_2_to_39(void)
{
    s32 index;
    u8 *base;
    u8 *entry;

    index = D_80012D52;

    if (index >= 0) {
        base = (u8 *)0x800121E8;

        index *= 4;

        entry = (u8 *)((u32)index + (unsigned long)base);

        if (*entry == 2) {
            *entry = 0x39;
        }
    }
}

/*
 * Loads a sound resource into the alternate buffer and optionally starts its sound set.
 *
 * MECHANISM: Frameless leaf; the absolute base selects lui/ori; in-place index *= 4 preserves
 * index- first addu order.
 */
s32 load_object_into_alternate_buffer(s16 object_index, s16 mode, s16 activate) {
    s16 activate_flag = activate;
    u16 saved_index = 0;
    register s16 saved_object_index = object_index;
    s16 saved_mode = mode;
    s16 activate_tail = (s16)activate_flag;
    s32 object_offset = (s32)object_index << 16;
    floor_generate_isolated_80286684_Object **objects = sound_stream_resource_entries;
    floor_generate_isolated_80286684_Object **slot =
        (floor_generate_isolated_80286684_Object **)((u8 *)objects + (object_offset >> 14));
    floor_generate_isolated_80286684_Object **buffers = sound_stream_buffer_entries;
    u16 buffer_index;
    floor_generate_isolated_80286684_Object *requested_object;
    floor_generate_isolated_80286684_Object *header_object;
    floor_generate_isolated_80286684_Object *load_object;
    u32 header;
    u32 buffer_addr;
    u32 mask_2;
    if (*slot == buffers[sound_stream_buffer_index]) {
        return 1;
    }

    if ((load_generation_resource_slot(1) << 16) != 0) {
        audio_load_sound_effect_bank(0xC);
    }
    {
        buffer_addr = (u32)(activate_flag << 16);
        if ((s32)buffer_addr == 0) {
            saved_index = (u16)sound_stream_buffer_index;
        }
    }

    buffer_index = (u16)sound_stream_buffer_index;
    requested_object = *slot;
    buffer_index ^= 1;
    sound_stream_buffer_index = buffer_index;
    if (requested_object != buffers[(s16)buffer_index]) {
        if (sound_stream_state_index != (s16)mode) {
            wait_until_sound_idle();
        }

        header_object = *slot;
        mask_2 = 0xFF800000;
        header_object->field_0 &= mask_2;
        load_object = *slot;
        header = load_object->field_0;
        {
            if (sound_stream_buffer_index != 0) {
                buffer_addr = (u32)sound_stream_secondary_marker_address & 0x007FFFFF;
            } else {
                buffer_addr = (u32)sound_stream_primary_marker_address & 0x007FFFFF;
            }
            header |= buffer_addr;
            buffer_addr = header;
        }
        {
            register s32 reload_left;
            register s32 reload_offset;
            register floor_generate_isolated_80286684_Object **reload_objects;
            s16 cd_command = 6;
            reload_left = (s32)saved_object_index << 16;
            load_object->field_0 = buffer_addr;
            reload_objects = sound_stream_resource_entries;
            reload_offset = reload_left >> 14;
            {
                floor_generate_isolated_80286684_Object **reload_slot = (floor_generate_isolated_80286684_Object **)((u8 *)reload_objects + reload_offset);
                Control_CD(cd_command, *reload_slot, 0);
                sound_stream_buffer_entries[sound_stream_buffer_index] = *reload_slot;
            }
            drain_cd_command_queue();
        }
    }

    load_sound_set(saved_mode);
    {
        s32 activate_tail_test =
            (s32)activate_tail << 16;
        if (activate_tail_test != 0) {
            s32 sound_command = 0x21;
            if (sound_stream_buffer_index != 0) {
                sound_command = 0x22;
            }
            SD_Call(sound_command);
            return 0;
        }
    }

    sound_stream_buffer_index = saved_index;
    return 0;
}

/* Loads a sound bank when its slot is stale and waits for its channel to become available. */
s32 load_generation_resource_slot(s16 resource_index) {
    s16 slot_index;
    s32 resource_id;
    u8 *loaded_id;
    floor_generate_isolated_80286894_S_80019894_0 *resource;
    void *cd_data;

    resource = (resource_index * 0xC) + (s8 *)&sound_effect_bank_descriptors;
    slot_index = resource->unk_00 - 1;
    loaded_id = slot_index + (u8 *)&sound_effect_loaded_record_ids;
    resource_id = resource_index + 1;
    if (*loaded_id == resource_id) {
        return 0;
    }
    SD_Call(0x72, resource_id);
    drain_audio_commands_and_service_channels();
    *loaded_id = resource_index + 1;
    DrawSync(0);
    VSync(0);
    cd_data = resource->unk_08;
    (*(s32 *)gpu_scratch_write_pointer) = ((Rec_D_80082E80 *)(&*(s32 *)&((SpriteFrameState *)gpu_scratch_buffer_base)->unk_00))->unk_00;
    Control_CD(6, cd_data, 0);
    Control_CD(6, resource->unk_04, 0);
    drain_cd_command_queue();
    set_sound_payload_slot(*(s32 *)&((SpriteFrameState *)gpu_scratch_buffer_base)->unk_00);
    SD_Call(((2 << slot_index) | 0x10) & 0xFFFF);
    drain_audio_commands_and_service_channels();
    do {
    } while (test_sound_channel_availability((s16) resource->unk_00) != 1);
    return 1;
}

/* Adds the marker at tile (8, 8) on floor 2 when the saved flag and matching entry allow it. */
s32 try_add_second_tower_entry(s16 entry_index) {
    u8 *entry;
    u8 *entries;

    if (dungeon_mode_state[0] == 0) {
        if (((s16 *)current_dungeon_floor)[0] == 2) {
            if (test_resident_bit(0xA2) != 0) {
                if ((count_matching_packed_entity_keys(0xC, 8) << 0x10) != 0) {
                    entries = (u8 *)((s16 *)dungeon_floor_marker_entries);
                    entry = entries;
                    entry += ((entry_index << 0x10) >> 0xD);
                    *(s16 *)(entry + 0) = 4;
                    *(s16 *)(entry + 2) = 8;
                    *(s16 *)(entry + 4) = 8;
                    *(s16 *)(entry + 6) = 0;
                    cycle_map_cell_flags(8, 8, TILE_HAS_OBJECT);
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* Sets g_dungeon_status.active_actor to one. */
void set_first_table_entry_active(void) {
    g_dungeon_status.active_actor = 1;
}

/* Assigns the given value to inactive cells inside the 64-by-64 generation grid. */
void fill_inactive_interior_cells(s16 value) {
    MapGrid *state;
    floor_generate_isolated_80286A84_DungeonCell *cells;
    s32 row;
    s32 column;

    state = &g_game_work.map;
    cells = ((floor_generate_isolated_80286A84_DungeonCell *)generation_cells);
    row = 1;
    do {
        column = 1;
        do {
            floor_generate_isolated_80286A84_DungeonCell *cell;
            unsigned long cellAddress;

            cellAddress = (column + (row << state->shiftX)) * 6;
            cellAddress += (unsigned long)cells;
            cell = (floor_generate_isolated_80286A84_DungeonCell *)cellAddress;
            if (cell->active == 0) {
                cell->value = value;
            }
            column++;
        } while (column < 0x3F);
        row++;
    } while (row < 0x3F);
}

/* Builds random rooms and connecting corridors, returning 1 when a corridor requires a retry. */
s32 generate_floor_layout(void)
{
    s8 flags[16];
    s32 conn[16];
    s16 dirv;
    s16 ox;
    s16 oy;
    s32 tries;
    s16 *hdr;
    u8 *bp;
    int full_height;
    s32 j;
    s32 jr;
    s32 i;
    s32 k;
    s32 ks;
    s32 n;
    s32 nt;
    s32 next;
    s32 rnd;
    s32 dir;
    s32 dw;
    s32 *cn;
    floor_generate_isolated_80286AF8_Room *dc;
    floor_generate_isolated_80286AF8_Room *rp;
    s32 rh;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    dc = (floor_generate_isolated_80286AF8_Room *) ((floor_generate_isolated_80286AF8_DungeonCfg *)((u8 *)&g_game_work + 476));
    j = 0;
    tries = 1024;
    rnd = generate_random_value();
    if ((rnd & 0x7F) == 0) {
        generation_room_columns = 2;
    }
    else
        if ((rnd & 0x1F) == 0) {
            generation_room_columns = 3;
        }
    else {
        generation_room_columns = 4;
    }
    rnd = generate_random_value();
    if ((rnd & 0x7F) == 0) {
        generation_room_rows = 2;
    }
    else
        if ((rnd & 0x1F) == 0) {
            generation_room_rows = 3;
        }
    else {
        generation_room_rows = 4;
    }
    for (i = 32; i > 0; i--) {
        ((floor_generate_isolated_80286AF8_Pair *)generation_room_link_pairs)[i].b = 0;
        ((floor_generate_isolated_80286AF8_Pair *)generation_room_link_pairs)[i].a = 0;
    }

    (*(s16 *)generation_room_link_count) = 0;
    if (((s16) random_dungeon_range_16(0, 512)) < 2) {
        j = 1;
    }
    else {
        oy = (generation_room_rows * generation_room_columns) - 1;
        k = 0;
        while (oy >= 0) {
            flags[k] = (generate_random_value() & 3) != 0;
            oy--;
            conn[k] = 0;
            k++;
        }

        for (oy = 0; oy < generation_room_rows; oy++) {
            for (ox = 0; ox < generation_room_columns; ox++) {
                k = (oy * generation_room_columns) + ox;
                if (flags[k] > 0) {
                    s32 rx;
                    s32 ry;
                    rx = random_dungeon_range_16(0, ((64 / generation_room_columns) / 2) - 1) + (ox * (64 / generation_room_columns));
                    ry = random_dungeon_range_16(0, ((64 / generation_room_rows) / 2) - 1) + (oy * (64 / generation_room_rows));
                    dw = random_dungeon_range_16(0, ((64 / generation_room_columns) / 2) - 1);
                    jr = random_dungeon_range_16(0, ((64 / generation_room_rows) / 2) - 1) + 5;
                    rh = jr;
                    do {
                    } while (0);
                    if (((s16) jr) < 5) {
                        rh = 5;
                    }
                    x0 = (s16) (rx - 2);
                    y0 = (s16) (ry - 2);
                    x1 = (s16) (dw + 9);
                    y1 = (s16) (rh + 4);
                    if (find_first_nonzero_rectangle_field(x0, y0, x1, y1) == 0) {
                        dungeon_rooms[k].active = 1;
                        fill_generation_cell_marks(x0, y0, x1, y1, k + 1);
                        dungeon_rooms[k].x = rx + 1;
                        dungeon_rooms[k].y = ry + 1;
                        dungeon_rooms[k].w = dw + 3;
                        dungeon_rooms[k].h = rh - 2;
                        dungeon_rooms[k].unk_08 = generate_random_value() & 0x60;
                        j++;
                        flags[k] = 2;
                        conn[k] += 0x01010101;
                    }
                    else {
                        s32 sy;
                        s32 sx;
                        flags[k] = 0;
                        sx = ((ox * (64 / generation_room_columns)) + (generate_random_value() & 7)) + 6;
                        sy = (oy * (64 / generation_room_rows)) + (generate_random_value() & 7);
                        sy = sy + 6;
                        dungeon_rooms[k].x = sx;
                        dungeon_rooms[k].y = sy;
                        generation_cells[(((s16) sy) << ((floor_generate_isolated_80286AF8_DungeonCfg *) dc)->shift_x) + ((s16) sx)].value =
                            generate_random_value() & 0x60;
                    }
                }
                else {
                    s32 sy;
                    s32 sx;
                    sx = ((ox * (64 / generation_room_columns)) + (generate_random_value() & 7)) + 6;
                    sy = (oy * (64 / generation_room_rows)) + (generate_random_value() & 7);
                    sy = sy + 6;
                    dungeon_rooms[k].x = sx;
                    dungeon_rooms[k].y = sy;
                    generation_cells[(((s16) sy) << ((floor_generate_isolated_80286AF8_DungeonCfg *) dc)->shift_x) + ((s16) sx)].value =
                        generate_random_value() & 0x60;
                }
            }

        }

    }
    clear_thirty_six_table_fields();
    hdr = ((s16 *)floor_generation_state);
    hdr[3] = j;
    if (((s16) j) < 2) {
        hdr[3] = 1;
        dungeon_rooms[0].x = 2;
        dungeon_rooms[0].y = 2;
        full_height = 1 << ((floor_generate_isolated_80286AF8_DungeonCfg *) dc)->shift_y;
        dungeon_rooms[0].active = 1;
        dungeon_rooms[0].w = (1 << ((floor_generate_isolated_80286AF8_DungeonCfg *) dc)->shift_x) - 4;
        dungeon_rooms[0].h = full_height - 4;
        dungeon_rooms[0].unk_08 = generate_random_value() & 0x60;
        update_region_until_complete(&dungeon_rooms[0], 0);
    }
    else {
        floor_generate_isolated_80286AF8_Room *room;
        s32 x;
        for (oy = 0; oy < generation_room_rows; oy++) {
            for (ox = 0; ox < generation_room_columns; ox++) {
                k = (oy * generation_room_columns) + ox;
                if (dungeon_rooms[k].active != 0) {
                    update_region_until_complete(&dungeon_rooms[k], k);
                }
            }

        }

        fill_inactive_interior_cells(16384);
        k = (generate_random_value() & 0xFFFF) % (generation_room_rows * generation_room_columns);
        dir = generate_random_value() & 6;
        rp = dungeon_rooms;
        while (1) {
            n = generation_room_rows * generation_room_columns;
            if (n <= 0) {
                break;
            }
            i = 0;
            do {
                if (!((flags[k] > 0) && (rp[k].active != 0))) {
                    k++;
                    k = k % n;
                    i++;
                }
                else {
                    break;
                }
            }
            while (i < n);
            if (i >= (generation_room_rows * generation_room_columns)) {
                break;
            }
            i = 4;
            oy = k / generation_room_columns;
            ox = k % generation_room_columns;
            next = k;
            x = k << 2;
            cn = conn;
            j = ((s32) cn) + x;
            ks = (s16) k;
            room = (floor_generate_isolated_80286AF8_Room *) ((((x + k) << 2)) + ((long)rp));
            do {
                rh = (s16) dir;
                bp = (u8 *) (j + (((u32) (dir << 16)) >> 17));
                if ((*bp) != 0) {
                    dirv = dir;
                    reset_generation_link_scratch();
                    next = search_outward_for_eligible_tile(&dirv, ox, oy, flags, cn, 1, ks);
                    if (next >= 0) {
                        u8 *bq;
                        s32 idx;
                        if (connect_rooms_with_corridor(rh, dirv, ks, next, flags) != 0) {
                            return 1;
                        }
                        bq = (u8 *) (&cn[next]);
                        (*bp)--;
                        bq[((dirv + 4) & 7) >> 1]--;
                        x0 = (s32) (&(*(s16 *)generation_room_link_count));
                        idx = ((s16 *) x0)[0];
                        room->link = 1;
                        rp[next].link = 1;
                        do {
                        } while (0);
                        n = (s32) ((floor_generate_isolated_80286AF8_Pair *)generation_room_link_pairs);
                        do {
                            ((floor_generate_isolated_80286AF8_Pair *) n)[idx].a = k;
                        } while (0);
                        ((floor_generate_isolated_80286AF8_Pair *) n)[((s16 *) x0)[0]].b = next;
                        ((s16 *) x0)[0]++;
                        break;
                    }
                }
                i--;
                dir = (dir + 2) & 6;
            }
            while (i > 0);
            if (i <= 0) {
                n = generation_room_rows * generation_room_columns;
                j = (k + 1) % n;
                for (i = 0; i < n; i++) {
                    if ((rp[j].link != 0) && (flags[j] > 0)) {
                        break;
                    }
                    j++;
                    j = j % n;
                }

                next = j;
            }
            else {
                dir = (((u16) dirv) + 2) & 7;
                flags[k]--;
                if (flags[k] <= 0) {
                    flags[k] = -1;
                }
            }
            k = next;
            tries--;
            if (tries < 0) {
                i = (generation_room_rows * generation_room_columns) - 1;
                for (; i >= 0; i--) {
                    if ((rp[i].link == 0) && (rp[i].active != 0)) {
                        clear_region_grid_rectangle(&rp[i]);
                    }
                }
                break;
            }
        }
        generation_unflagged_room_count = 0;

        nt = generation_room_rows * generation_room_columns;
        for (i = 0; i < nt; i++) {
            if ((dungeon_rooms[i].flags == 0) && (dungeon_rooms[i].active != 0)) {
                generation_unflagged_room_count++;
            }
        }

    }
    rnd = jr;
    compact_generation_regions();
    clear_generation_cell_masks();
    update_active_area_tiles();
    return 0;
}

/*
 * Clears four blocked-direction marks, resets the forward limit to the room-column count, and
 * clears both side-mark rows.
 */
void reset_generation_link_scratch(void) {
    s32 entry_index;

    ((u8 *)generation_blocked_direction_marks)[0] = ((u8 *)generation_blocked_direction_marks)[1] = ((u8 *)generation_blocked_direction_marks)[2] = ((u8 *)generation_blocked_direction_marks)[3] = 0;
    generation_search_forward_limit = generation_room_columns;

    for (entry_index = generation_room_columns - 1; entry_index >= 0; entry_index--) {
        u8* entry = &((u8 *)generation_search_side_marks_alias)[entry_index];

        entry[0] = 0;
        entry[4] = 0;
    }
}

/* C89 default promotions keep the public final argument a word while this
 * definition gives the filter its original signed-halfword view. */
/* Searches outward for an eligible unlinked room, updating direction and blocked-search limits, or
   returns -1. */
s16 search_outward_for_eligible_tile(facing, origin_x, origin_y, tiles, search_arg, radius, filter_arg)
u16 *facing;
s32 origin_x, origin_y;
s8 *tiles;
s32 search_arg, radius;
s16 filter_arg;
{
    u16 start_x;
    u16 start_y;
    u16 saved_radius;
    u16 saved_filter;
    s32 forward_limit;
    s32 search_radius;
    s32 facing_high;
    s32 facing_offset;
    u16 tile_index_u16;
    u8 * initial_x_steps;
    s32 x;
    s32 y;
    s32 failures;
    s16 tile_index;
    s8 tile;
    s32 forward_steps;
    s32 sides_left;
    s32 side;
    s32 side_steps;
    s32 turn_dir;
    s32 forward_dir;
    s32 forward_offset;
    s32 turn_offset;
    u16 next_x;
    u16 next_y;
    s32 x_steps_base;
    s32 y_steps_base;
    s8 *blocked;
    s8 *map_base;
    s8 *side_marks;

    facing_high = (s32)*facing << 16;
    initial_x_steps = ((u8 *)dir_step_x);
    facing_offset = facing_high >> 15;
    start_x = origin_x;
    start_y = origin_y;
    saved_radius = radius;
    failures = 0;
    x = origin_x + *(u16 *)(initial_x_steps + facing_offset) * radius;
    y = origin_y + *(u16 *)(((u8 *)dir_step_y) + facing_offset) * radius;

    saved_filter = filter_arg;

    if (((s16)x >= 0) && ((s16)x < generation_room_columns) && ((s16)y >= 0) &&
        ((s16)y < generation_room_rows) && (((s8 *)generation_blocked_direction_marks)[facing_high >> 17] == 0)) {
        tile_index_u16 = x + (s16)y * generation_room_columns;
        tile_index = (s16)tile_index_u16;
        tile = tiles[tile_index];
        if (tile > 0) {
            if (has_generation_link_within_pair(tile_index, (s16)filter_arg) == 0) {
                return tile_index;
            }
            failures = 1;
        } else if (tile < 0) {
            failures = 1;
        }
    } else {
        failures++;
    }

    if (failures != 0) {
        ((s8 *)generation_blocked_direction_marks)[((s32)*facing << 16) >> 17] = 1;
        if ((s16)saved_radius < (s8)generation_search_forward_limit) {
            generation_search_forward_limit = saved_radius;
        }
    }

    if ((s16)saved_radius > (s8)generation_search_forward_limit) {
        forward_limit = (s8)generation_search_forward_limit;
    } else {
        forward_limit = (s16)saved_radius;
    }

    forward_steps = 1;
    if (forward_steps < (s16)saved_radius) {
        search_radius = (s16)saved_radius;
        do {
            sides_left = 2;
            if (forward_steps >= forward_limit) {
                failures++;
            } else {
                side_steps = search_radius - forward_steps;
                side = generate_random_value() & 1;
                x_steps_base = (s32)((u8 *)dir_step_x);
                y_steps_base = (s32)((u8 *)dir_step_y);
                for (; sides_left > 0; sides_left--, side ^= 1) {
                    forward_dir = *(s16 *)facing;
                    forward_offset = forward_dir * 2;
                    turn_dir = (forward_dir + generation_search_turn_offsets[side]) & 6;
                    turn_offset = turn_dir * 2;
                    next_x = start_x + *(s16 *)(forward_offset + x_steps_base) * forward_steps
                    + *(s16 *)(turn_offset + x_steps_base) * side_steps;
                    next_y = start_y + *(s16 *)(forward_offset + y_steps_base) * forward_steps
                    + *(s16 *)(turn_offset + y_steps_base) * side_steps;
                    if (((s16)next_x >= 0) && ((s16)next_x < generation_room_columns) &&
                        ((s16)next_y >= 0) && ((s16)next_y < generation_room_rows)) {
                        map_base = ((s8 *)generation_search_side_marks_alias);
                        side_marks = map_base + side * 4;
                        blocked = side_marks + forward_steps;
                        if (*blocked == 0) {
                            tile_index_u16 = next_x + (s16)next_y * generation_room_columns;
                            tile_index = (s16)tile_index_u16;
                            map_base = tiles;
                            tile = map_base[tile_index];
                            if (tile == 0) {
                                continue;
                            }
                            if (tile > 0) {
                                if (has_generation_link_within_pair(tile_index, (s16)saved_filter) == 0) {
                                    *facing = turn_dir;
                                    return tile_index;
                                }
                            }
                            *blocked = 1;
                        }
                    }
                    failures++;
                }
            }
            forward_steps++;
        } while (forward_steps < search_radius);
    }

    if (failures < 3) {
        return search_outward_for_eligible_tile(facing, (s16)start_x, (s16)start_y, tiles, search_arg,
                             (s16)(saved_radius + 1), (s16)saved_filter);
    }
    return -1;
}

/* Reports whether the two room indices already appear together in the generation link list. */
s32 has_generation_link_within_pair(s16 value_a, s16 value_b)
{
    s32 pair_index;
    s32 first;
    s32 second;
    u8 *pairs;
    u8 *pair;
    u8 value;

    pair_index = ((s16 *)generation_room_link_count)[0] - 1;
    if (pair_index >= 0) {
        first = value_a;
        second = value_b;
        pairs = ((u8 *)generation_room_link_pairs);
        pair = pairs + pair_index * 2;
        do {
            value = pair[0];
            if (((value == first) || (value == second)) &&
                (((value = pair[1]) == first) || (value == second))) {
                return 1;
            }
            pair_index--;
            pair -= 2;
        } while (pair_index >= 0);
    }

    return 0;
}

/* Connects two rooms with a two-cell-wide corridor, returning 1 when the height changes cannot fit. */
s16 connect_rooms_with_corridor(s16 src_dir, s16 dest_dir, s16 src_idx, s16 dest_idx, u8 *room_marks) {
    floor_generate_isolated_80287C4C_Pos start;
    floor_generate_isolated_80287C4C_Pos end;
    floor_generate_isolated_80287C4C_Pos side_start;
    s16 src_offset_x;
    s16 src_offset_y;
    s16 dest_offset_x;
    s16 dest_offset_y;
    s16 join_x;
    s16 join_y;
    s32 main_height[1];
    s32 height_step[1];
    s32 side_height[1];
    s32 dest_x;
    s32 dest_y;
    s16 back_dir;
    floor_generate_isolated_80287C4C_Room *src_room;
    s16 path_length;
    s16 saved_dir;
    floor_generate_isolated_80287C4C_Room *dest_room;
    MapGrid *dungeon;
    floor_generate_isolated_80287C4C_DungeonCell *edge_cell;
    floor_generate_isolated_80287C4C_DungeonCell *inner_cell;
    s16 travel_dir;
    s16 entry_dir;
    s16 room_idx;
    s16 dest_grid_x;
    s16 dest_grid_y;
    s32 src_x;
    s32 src_y;
    s32 cursor_x;
    s32 cursor_y;
    s32 src_height;
    s32 dest_height;
    s32 height_delta;
    s32 height_gap;

    dungeon = &g_game_work.map;
    src_room = &dungeon_rooms[src_idx];
    dest_room = &dungeon_rooms[dest_idx];
    path_length = 0;
    pick_relative_room_edge_point(src_dir, &src_offset_x, &src_offset_y, src_room);
    pick_relative_room_edge_point((dest_dir + 4) & 6, &dest_offset_x, &dest_offset_y, dest_room);
    travel_dir = src_dir;
    saved_dir = src_dir;
    if (dungeon_rooms[src_idx].active) {
        append_generation_region_entry(src_idx, src_room->x + src_offset_x, src_room->y + src_offset_y, 0);
    }
    if (dungeon_rooms[dest_idx].active) {
        append_generation_region_entry(dest_idx, dest_room->x + dest_offset_x, dest_room->y + dest_offset_y, 0);
    }
    save_or_restore_random_seed(1);
    start.x = src_room->x + src_offset_x;
    start.y = src_room->y + src_offset_y;
    start.dir = src_dir;
    if (dungeon_rooms[src_idx].active) {
        start.x = start.x + dir_step_x[travel_dir];
        start.y = start.y + dir_step_y[travel_dir];
    }
    cursor_x = (s16)(src_idx % generation_room_columns) + dir_step_x[travel_dir];
    cursor_y = (s16)(src_idx / generation_room_columns) + dir_step_y[travel_dir];
    dest_grid_x = dest_idx % generation_room_columns;
    dest_grid_y = dest_idx / generation_room_columns;
    for (;;) {
        if (cursor_x == dest_grid_x && cursor_y == dest_grid_y) {
            if (dungeon_rooms[dest_idx].active) {
                end.x = dest_room->x + dest_offset_x;
                end.y = dest_room->y + dest_offset_y;
            } else {
                end.x = dest_room->x;
                end.y = dest_room->y;
            }
            end.x = end.x - dir_step_x[dest_dir];
            end.y = end.y - dir_step_y[dest_dir];
            path_length += choose_next_step_toward_destination(&start, &end, 1, &join_x, &join_y);
            start.x = start.x + dir_step_x[(travel_dir + 2) & 7];
            start.y = start.y + dir_step_y[(travel_dir + 2) & 7];
            end.x = end.x + dir_step_x[(dest_dir + 2) & 7];
            end.y = end.y + dir_step_y[(dest_dir + 2) & 7];
            join_x = join_x - dir_step_x[travel_dir];
            join_y = join_y - dir_step_y[travel_dir];
            choose_next_step_toward_destination(&start, &end, 0, &join_x, &join_y);
            break;
        }
        room_idx = cursor_y * generation_room_columns + cursor_x;
        room_marks[room_idx] = 2;
        end.x = dungeon_rooms[room_idx].x;
        end.y = dungeon_rooms[room_idx].y;
        path_length += choose_next_step_toward_destination(&start, &end, 1, &join_x, &join_y);
        side_start = start;
        side_start.x = side_start.x + dir_step_x[(travel_dir + 2) & 7];
        side_start.y = side_start.y + dir_step_y[(travel_dir + 2) & 7];
        join_x = join_x - dir_step_x[travel_dir];
        join_y = join_y - dir_step_y[travel_dir];
        choose_next_step_toward_destination(&side_start, &end, 0, &join_x, &join_y);
        start.x = end.x;
        start.y = end.y;
        if (dir_step_x[travel_dir] != 0) {
            if (cursor_x == dest_grid_x) {
                start.dir = (calculate_planar_heading(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        } else {
            if (cursor_y == dest_grid_y) {
                start.dir = (calculate_planar_heading(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        }
        cursor_x = cursor_x + dir_step_x[start.dir];
        cursor_y = cursor_y + dir_step_y[start.dir];
        travel_dir = start.dir;
    }

    travel_dir = saved_dir;
    back_dir = (travel_dir + 4) & 7;
    src_x = src_room->x + src_offset_x;
    src_y = src_room->y + src_offset_y;
    edge_cell = &generation_cells[(src_y << dungeon->shiftX) + src_x];
    inner_cell = &generation_cells[((src_y + dir_step_y[back_dir]) << dungeon->shiftX) + src_x + dir_step_x[back_dir]];
    dest_x = dest_room->x + dest_offset_x;
    dest_y = dest_room->y + dest_offset_y;
    if (is_value_within_inclusive_bounds(edge_cell->kind, 15, 18)) {
        edge_cell->kind = (inner_cell->flags >> 1) + (travel_dir / 2) * 5 + 79;
        edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
        if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
            edge_cell->value = edge_cell->value + 96;
        }
    }
    if (is_value_within_inclusive_bounds(inner_cell->kind, 19, 28)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
    } else if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
        inner_cell->value = inner_cell->value + 96;
    }

    cursor_x = src_x + dir_step_x[(travel_dir + 2) & 7];
    cursor_y = src_y + dir_step_y[(travel_dir + 2) & 7];
    edge_cell = &generation_cells[(cursor_y << dungeon->shiftX) + cursor_x];
    inner_cell = &generation_cells[((cursor_y + dir_step_y[back_dir]) << dungeon->shiftX) + cursor_x + dir_step_x[back_dir]];
    if (is_value_within_inclusive_bounds(edge_cell->kind, 15, 18)) {
        edge_cell->kind = (inner_cell->flags >> 1) + (travel_dir / 2) * 5 + 79;
        edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
        if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
            edge_cell->value = edge_cell->value + 96;
        }
    }
    if (is_value_within_inclusive_bounds(inner_cell->kind, 19, 28)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
    } else if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
        inner_cell->value = inner_cell->value + 96;
    }

    if (dungeon_rooms[dest_idx].active) {
        back_dir = dest_dir;
        cursor_x = dest_x;
        cursor_y = dest_y;
        edge_cell = &generation_cells[(cursor_y << dungeon->shiftX) + cursor_x];
        cursor_x = cursor_x + dir_step_x[dest_dir];
        cursor_y = cursor_y + dir_step_y[dest_dir];
        inner_cell = &generation_cells[(cursor_y << dungeon->shiftX) + cursor_x];
        entry_dir = (dest_dir + 4) & 6;
        if (is_value_within_inclusive_bounds(edge_cell->kind, 15, 18)) {
            edge_cell->kind = (inner_cell->flags >> 1) + (entry_dir / 2) * 5 + 79;
            edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
            if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
                edge_cell->value = edge_cell->value + 96;
            }
        }
        if (is_value_within_inclusive_bounds(inner_cell->kind, 19, 28)) {
            inner_cell->kind = inner_cell->flags + (entry_dir / 2) * 10 + 39;
        } else if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
            inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
            inner_cell->value = inner_cell->value + 96;
        }

        cursor_x = dest_x + dir_step_x[(entry_dir - 2) & 7];
        cursor_y = dest_y + dir_step_y[(entry_dir - 2) & 7];
        edge_cell = &generation_cells[(cursor_y << dungeon->shiftX) + cursor_x];
        inner_cell = &generation_cells[((cursor_y + dir_step_y[back_dir]) << dungeon->shiftX) + cursor_x + dir_step_x[back_dir]];
        if (is_value_within_inclusive_bounds(edge_cell->kind, 15, 18)) {
            edge_cell->kind = (inner_cell->flags >> 1) + (entry_dir / 2) * 5 + 79;
            edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
            if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
                edge_cell->value = edge_cell->value + 96;
            }
        }
        if (is_value_within_inclusive_bounds(inner_cell->kind, 19, 28)) {
            inner_cell->kind = inner_cell->flags + (entry_dir / 2) * 10 + 39;
        } else if (is_value_within_inclusive_bounds(inner_cell->kind, 99, 103)) {
            inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
            inner_cell->value = inner_cell->value + 96;
        }
    }

    save_or_restore_random_seed(0);
    travel_dir = saved_dir;
    if (dungeon_rooms[src_idx].active) {
        src_height = generation_cells[((src_room->y + src_offset_y) << dungeon->shiftX) + src_room->x + src_offset_x].value;
    } else {
        src_height = generation_cells[(src_room->y << dungeon->shiftX) + src_room->x].value;
    }
    if (dungeon_rooms[dest_idx].active) {
        dest_height = generation_cells[((dest_room->y + dest_offset_y) << dungeon->shiftX) + dest_room->x
            + dest_offset_x].value;
    } else {
        dest_height = generation_cells[(dest_room->y << dungeon->shiftX) + dest_room->x].value;
    }
    if (path_length == 0) {
        path_length = 1;
    }
    height_delta = dest_height - src_height;
    height_gap = __builtin_abs(height_delta);
    if ((height_gap + 31) / 32 > path_length) {
failed:
        return 1;
    }
    height_step[0] = (height_gap << 16) / path_length;
    if (dest_height < src_height) {
        height_step[0] = -height_step[0];
    }
    main_height[0] = side_height[0] = src_height << 16;

    start.x = src_room->x + src_offset_x;
    start.y = src_room->y + src_offset_y;
    start.dir = travel_dir;
    if (dungeon_rooms[src_idx].active) {
        start.x = start.x + dir_step_x[travel_dir];
        start.y = start.y + dir_step_y[travel_dir];
    }
    cursor_x = (s16)(src_idx % generation_room_columns) + dir_step_x[travel_dir];
    cursor_y = (s16)(src_idx / generation_room_columns) + dir_step_y[travel_dir];
    dest_grid_x = dest_idx % generation_room_columns;
    dest_grid_y = dest_idx / generation_room_columns;
    for (;;) {
        if (cursor_x == dest_grid_x && cursor_y == dest_grid_y) {
            if (dungeon_rooms[dest_idx].active) {
                end.x = dest_room->x + dest_offset_x;
                end.y = dest_room->y + dest_offset_y;
            } else {
                end.x = dest_room->x;
                end.y = dest_room->y;
            }
            end.x = end.x - dir_step_x[dest_dir];
            end.y = end.y - dir_step_y[dest_dir];
            if (carve_corridor_toward_destination(&start, &end, 1, &join_x, &join_y, main_height, height_step) < 0) {
                return 1;
            }
            start.x = start.x + dir_step_x[(travel_dir + 2) & 7];
            start.y = start.y + dir_step_y[(travel_dir + 2) & 7];
            end.x = end.x + dir_step_x[(dest_dir + 2) & 7];
            end.y = end.y + dir_step_y[(dest_dir + 2) & 7];
            join_x = join_x - dir_step_x[travel_dir];
            join_y = join_y - dir_step_y[travel_dir];
            if (carve_corridor_toward_destination(&start, &end, 0, &join_x, &join_y, side_height, height_step) < 0) {
                goto failed;
            }
            break;
        }
        room_idx = cursor_y * generation_room_columns + cursor_x;
        room_marks[room_idx] = 2;
        end.x = dungeon_rooms[room_idx].x;
        end.y = dungeon_rooms[room_idx].y;
        if (carve_corridor_toward_destination(&start, &end, 1, &join_x, &join_y, main_height, height_step) < 0) {
            return 1;
        }
        side_start = start;
        side_start.x = side_start.x + dir_step_x[(travel_dir + 2) & 7];
        side_start.y = side_start.y + dir_step_y[(travel_dir + 2) & 7];
        join_x = join_x - dir_step_x[travel_dir];
        join_y = join_y - dir_step_y[travel_dir];
        if (carve_corridor_toward_destination(&side_start, &end, 0, &join_x, &join_y, side_height, height_step) < 0) {
            return 1;
        }
        start.x = end.x;
        start.y = end.y;
        if (dir_step_x[travel_dir] != 0) {
            if (cursor_x == dest_grid_x) {
                start.dir = (calculate_planar_heading(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        } else {
            if (cursor_y == dest_grid_y) {
                start.dir = (calculate_planar_heading(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        }
        cursor_x = cursor_x + dir_step_x[start.dir];
        cursor_y = cursor_y + dir_step_y[start.dir];
        travel_dir = start.dir;
    }
    return 0;
}

/* Chooses or reuses corridor bends, marks its route, and returns the number of steps. */
s32 choose_next_step_toward_destination(floor_generate_isolated_8028906C_Pos *start, floor_generate_isolated_8028906C_Pos *dest, s16 rnd, s16 *outX, s16 *outY) {
    s16 count;
    s16 cx;
    s16 cy;
    s32 dir;
    s16 dstX;
    s16 dstY;
    s16 dirSlot;
    s16 rangeX;
    s16 rangeY;
    s16 wx;
    s16 wy;
    s32 delta;
    s32 delta2;
    s32 icy;
    floor_generate_isolated_8028906C_DungeonState *st;

    count = 0;
    cy = start->y;
    cx = start->x;
    delta2 = cx;
    delta = (s32)(*(CoordPair *)dest << 16) >> 16;
    delta = delta - delta2;
    dir = (u16)start->dir;
    delta = __builtin_abs(delta);
    rangeX = delta - 4;
    delta2 = (s32)&g_game_work;
    dirSlot = dir;
    dstY = dest->y;
    st = (floor_generate_isolated_8028906C_DungeonState *)((u8 *)delta2 + 476);
    dstX = dest->x;
    if (rangeX <= 0) {
        rangeX = 1;
    }
    wx = rangeX;
    if (wx >= 5) {
        wx = 4;
    }
    rangeX = rangeX - wx;
    if (rangeX <= 0) {
        rangeX = 1;
    }

    icy = dstY;
    rangeY = __builtin_abs(icy - cy) - 4;
    if (rangeY <= 0) {
        rangeY = 1;
    }
    wy = rangeY;
    if (wy >= 5) {
        wy = 4;
    }
    rangeY = rangeY - wy;
    if (rangeY <= 0) {
        rangeY = 1;
    }

    if (rnd != 0) {
        s16 rr;

        rr = (u16)generate_random_value() % rangeX;
        *outX = rr;
        wx = cx + rr * dir_step_x[(s16)dir] + dir_step_x[(s16)dir] * wx;
        rr = (u16)generate_random_value() % rangeY;
        *outY = rr;
        wy = cy + rr * dir_step_y[(s16)dir] + dir_step_y[(s16)dir] * wy;
    } else {
        wx = cx + *outX * dir_step_x[(s16)dir] + dir_step_x[(s16)dir] * wx;
        wy = cy + *outY * dir_step_y[(s16)dir] + dir_step_y[(s16)dir] * wy;
    }

    for (;;) {
        s32 ix;
        s32 iy;

        iy = cy;
        ix = cx;
        ((floor_generate_isolated_8028906C_DungeonCell *)generation_cells)[(iy << st->stride) + ix].kind = 104;
        ((floor_generate_isolated_8028906C_DungeonCell *)generation_cells)[(iy << st->stride) + ix].flags = 1;
        if (ix == wx && iy == wy) {
            break;
        }
        count++;
        cx += dir_step_x[(s16)dir];
        cy += dir_step_y[(s16)dir];
    }

    if (wx != dstX || wy != dstY) {
        if (dir_step_x[dirSlot] != 0) {
            wy = dstY;
        } else {
            wx = dstX;
        }
        delta = calculate_planar_heading(cx, cy, wx, wy);
        for (;;) {
            s32 ix;
            s32 iy;

            iy = cy;
            ix = cx;
            ((floor_generate_isolated_8028906C_DungeonCell *)generation_cells)[(iy << st->stride) + ix].kind = 104;
            ((floor_generate_isolated_8028906C_DungeonCell *)generation_cells)[(iy << st->stride) + ix].flags = 1;
            if (ix == wx && iy == wy) {
                break;
            }
            count++;
            cx += dir_step_x[((u32)delta >> 9) & 6];
            cy += dir_step_y[((u32)delta >> 9) & 6];
        }
    }

    if (wx != dstX || wy != dstY) {
        delta = calculate_planar_heading(cx, cy, dstX, dstY);
        for (;;) {
            s32 ix;
            s32 iy;

            iy = cy;
            ix = cx;
            ((floor_generate_isolated_8028906C_DungeonCell *)generation_cells)[(iy << st->stride) + ix].kind = 104;
            ((floor_generate_isolated_8028906C_DungeonCell *)generation_cells)[(iy << st->stride) + ix].flags = 1;
            if (ix == dstX && iy == dstY) {
                break;
            }
            count++;
            cx += dir_step_x[((u32)delta >> 9) & 6];
            cy += dir_step_y[((u32)delta >> 9) & 6];
        }
    }
    return count;
}

/* Expand each leg in place so its registers and return path stay local. */
/* May return from the enclosing function and uses the caller locals. */
#define WALK_CORRIDOR(end_x, end_y) \
for (;;) { \
    s32 iy; \
    s32 ix; \
    s32 tile; \
    floor_generate_isolated_802895E4_DungeonCell *cell; \
    s32 d; \
 \
    tile = walker->tile & 0xFFE0; \
    iy = cy; \
    cell = &((floor_generate_isolated_802895E4_DungeonCell *)generation_cells)[(iy << st->shiftX) + (ix = cx)]; \
    if (cell->value != 16384) { \
        d = abs(cell->value - (s16)tile); \
        if (d >= 33) { \
            return -1; \
        } \
    } \
    cell->value = tile; \
    if (ix == (end_x) && iy == (end_y)) { \
        break; \
    } \
    *(s32 *)walker += *cost; \
    count++; \
    cx += dir_step_x[dir]; \
    cy += dir_step_y[dir]; \
}

/* Writes stepped corridor heights along the route, returning -1 for a height mismatch over 32. */
s16 carve_corridor_toward_destination(floor_generate_isolated_802895E4_Pos *start, floor_generate_isolated_802895E4_Pos *dest, s16 rnd, s16 *out_x, s16 *out_y,
                  floor_generate_isolated_802895E4_Walker *walker, s32 *cost) {
    s16 count;
    s16 cx;
    s16 cy;
    s16 dir;
    s16 dst_x;
    s16 dst_y;
    s16 dir_slot;
    s16 range_x;
    s16 range_y;
    s16 wx;
    s16 wy;
    s32 delta;
    s32 delta2;
    s32 idy;
    GameWork *gw;
    MapGrid *st;
    u32 r;

    count = 0;
    cy = start->y;
    cx = start->x;
    delta = dest->x;
    delta = delta - cx;
    dir = start->dir;
    delta = abs(delta);
    range_x = delta - 4;
    gw = &g_game_work;
    dir_slot = dir;
    dst_y = dest->y;
    dst_x = dest->x;
    if (range_x <= 0) {
        range_x = 1;
    }
    st = &gw->map;
    wx = range_x;
    if (wx >= 5) {
        wx = 4;
    }
    range_x = range_x - wx;
    if (range_x <= 0) {
        range_x = 1;
    }

    idy = (u32)(u16)dst_y << 16;
    idy >>= 16;
    delta = (u32)(u16)cy << 16;
    delta >>= 16;
    delta2 = abs(idy - delta);
    range_y = delta2 - 4;
    if (range_y <= 0) {
        range_y = 1;
    }
    wy = range_y;
    if (wy >= 5) {
        wy = 4;
    }
    range_y = range_y - wy;
    if (range_y <= 0) {
        range_y = 1;
    }

    if (rnd != 0) {
        s16 random_offset;

        random_offset = (u16)generate_random_value() % range_x;
        *out_x = random_offset;
        wx = cx + random_offset * dir_step_x[dir] + dir_step_x[dir] * wx;
        random_offset = (u16)generate_random_value() % range_y;
        *out_y = random_offset;
        wy = cy + random_offset * dir_step_y[dir] + dir_step_y[dir] * wy;
    } else {
        wx = cx + *out_x * dir_step_x[dir] + dir_step_x[dir] * wx;
        wy = cy + *out_y * dir_step_y[dir] + dir_step_y[dir] * wy;
    }

    WALK_CORRIDOR(wx, wy);

    if (wx != dst_x || wy != dst_y) {
        if (dir_step_x[dir_slot] != 0) {
            wy = dst_y;
        } else {
            wx = dst_x;
        }
        r = calculate_planar_heading(cx, cy, wx, wy);
        dir = (r >> 9) & 6;
        WALK_CORRIDOR(wx, wy);
    }

    if (wx != dst_x || wy != dst_y) {
        r = calculate_planar_heading(cx, cy, dst_x, dst_y);
        dir = (r >> 9) & 6;
        WALK_CORRIDOR(dst_x, dst_y);
    }
    return count;
}

#undef WALK_CORRIDOR

/* Tries perpendicular directions when the next cell is flagged; otherwise keeps the direction. */
s16 choose_unblocked_cardinal_direction(s16 x, s16 y, s16 dir)
{
    s32 turn;
    s32 d;
    s16 nx;
    s16 ny;
    MapGrid *map = &g_game_work.map;

    nx = x + dir_step_x[dir];
    ny = y + dir_step_y[dir];
    if (generation_cells[(ny << map->shiftX) + nx].flags != 0) {
        for (turn = 2; turn < 7; turn += 4) {
            d = (dir + turn) & 6;
            nx = x + dir_step_x[d];
            ny = y + dir_step_y[d];
            if (generation_cells[(ny << map->shiftX) + nx].flags == 0) {
                return (dir + turn) & 6;
            }
        }
    }
    return dir;
}

/* Chooses a random point just outside the requested room edge, or (0, 0) for an inactive room. */
void pick_relative_room_edge_point(s16 side, s16 *out_x, s16 *out_y, floor_generate_isolated_80289CEC_Entry *room) {
    if (room->fieldA == 0) {
        *out_x = 0;
        *out_y = 0;
        return;
    }

    switch (side) {
    case 0:
        *out_x = room->field4;
        *out_y = ((u16)generate_random_value() % (room->field6 - 2)) + 1;
        break;

    case 2:
        *out_x = ((u16)generate_random_value() % (room->field4 - 2)) + 1;
        *out_y = room->field6;
        break;

    case 4:
        *out_x = -1;
        *out_y = ((u16)generate_random_value() % (room->field6 - 2)) + 1;
        break;

    default:
        *out_x = ((u16)generate_random_value() % (room->field4 - 2)) + 1;
        *out_y = -1;
        break;
    }
}

/* MECHANISM: The two output pointers and record pointer stay live across RNG calls,
   naturally producing the retail s1/s2/s0 hold set and 0x20-byte frame.
   Each mode selects a copy/random/-1 pair using exact halfword field widths. */

s32 is_value_within_inclusive_bounds(s16 value, s32 lower_bound, s16 upper_bound)
{
    s32 in_range;
    s32 scaled_lower_bound;
    in_range = 0;
    scaled_lower_bound = lower_bound << 0x10;
    if ((value << 0x10) >= scaled_lower_bound) {
        in_range = upper_bound >= value;
    }
    return in_range;
}

/* Regenerates a room's terrain and features until its eligible tiles pass the traversal check. */
void update_region_until_complete(Rec_func_8001CE44_arg0 *region, s16 update_id) {
    do {
        fill_region_with_random_patches(region, update_id);
        /*
         * BUG: special rooms place items and traps before the path check. A retry redraws terrain without
         * clearing those records, leaving placements on the old layout.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        choose_random_region_feature(region, update_id);
    } while ((mark_path_through_neighboring_tiles(update_id) << 0x10) == 0);
    mask_generation_cell_rect(region->unk_00, region->unk_02, region->unk_04, region->unk_06, 0xF);
}

/* Changes tile kind, height, and flags at a randomly chosen coordinate parity within the room. */
void adjust_random_parity_tile_heights(floor_generate_isolated_80289EC0_Rect *rect, s32 rng_input_1)
{
    MapGrid *dungeon = &g_game_work.map;
    s32 parity;
    s32 x_end;
    s32 y_end;
    s32 x;
    s32 y;
    s32 initial_y;
    s32 initial_x;
    s32 initial_width;
    s32 initial_height;
    s32 y_parity;
    floor_generate_isolated_80289EC0_Tile *tile;

    parity = generate_random_value() & 1;
    initial_y = rect->y;
    initial_x = rect->x;
    initial_width = rect->width;
    initial_height = rect->height;
    x_end = initial_x + initial_width;
    y_end = initial_y + initial_height;
    y = initial_y;

    if (y < y_end) {
        do {
            x = rect->x;
            if (x < x_end) {
                y_parity = y & 1;
                do {
                    if (((x & 1) == parity) && (y_parity == parity)) {
                        tile = (floor_generate_isolated_80289EC0_Tile *) (((u8 *)generation_cells) +
                            (((y << dungeon->shiftX) + x) * 6));
                        tile->height = (tile->flags >> 1) + 0x63;
                        tile->y -= 0x60;
                        tile->flags |= 0x8000;
                    }
                    x++;
                } while (x < x_end);
            }
            y++;
        } while (y < y_end);
    }
}

/* Adds a room-sized special object in a free floor slot unless floor flags disable it. */
void initialize_random_room_slot(void *room, s32 unused)
{
    u8 *slot_data;
    s16 raw_size;
    s16 size;
    s32 room_area;
    s32 random_bonus;
    s32 x_offset;
    s32 y_roll;
    s32 slot_index;
    int y_offset;
    u8 *slot_info;
    if (!((dungeon_floor_flags) & 0x10000000)) {
        random_bonus = generate_random_value() & 7;
        room_area = (*((u16 *) (((s8 *) room) + 6))) * (*((u16 *) (((s8 *) room) + 4)));
        raw_size = (room_area >> 2) + random_bonus;
        size = raw_size;
        if (raw_size >= 0x1D) {
            size = 0x1C;
        }
        slot_index = 0;
        for (; slot_index < 0x20; slot_index++) {
            slot_info = (u8 *)((u32 *)((u8 *)floor_objects) + slot_index);
            slot_data = (u8 *)((u8 *)dungeon_floor_object_positions) + slot_index * 0x18;
            if ((*((u8 *) (((s8 *) slot_info) + 1))) == 0) {
                x_offset = random_dungeon_range_16(0, ((*((u16 *) (((s8 *) room) + 4))) - 1) & 0xFFFF) & 0xFFFF;
                y_roll = random_dungeon_range_16(0, ((*((u16 *) (((s8 *) room) + 6))) - 1) & 0xFFFF);
                y_offset = y_roll & 0xFFFF;
                *((s8 *) (((s8 *) slot_data) + 6)) = (s8) ((*((u8 *) (((s8 *) room) + 0))) + x_offset);
                *((s8 *) (((s8 *) slot_data) + 7)) = (s8) ((*((u8 *) (((s8 *) room) + 2))) + y_offset);
                *((u8 *) (((s8 *) slot_info) + 0)) = 0x13;
                *((u8 *) (((s8 *) slot_info) + 1)) = 0x15U;
                *((u8 *) (((s8 *) slot_info) + 3)) = (u8) 0xC0;
                *((s8 *) (((s8 *) slot_info) + 2)) = (s8) size;
                *((s32 *) (((s8 *) slot_data) + 8)) = 0;
                return;
            }
        }
    }
}

/* Places randomly chosen traps on eligible room tiles and marks those tiles occupied. */
void place_room_trap_records(floor_generate_isolated_8028A0F4_DungeonRect *rect, s32 update_id)
{
    u16 tile_flags;
    s32 slot_limit_calc;
    s16 slot_limit;
    s32 item_kind;
    s16 stored_kind;
    s32 special_roll;
    s32 slot_index;
    u32 kind_roll;
    u16 item_flags;
    floor_generate_isolated_8028A0F4_DungeonGroup *item_category_table;
    u32 x_offset;
    u32 y_offset;

    special_roll = generate_random_value() & 0xFF;
    slot_limit_calc = ((rect->height * rect->width) >> 3) +
                 (generate_random_value() & 7);
    slot_limit = slot_limit_calc;
    if ((s16)slot_limit_calc >= 29) {
        slot_limit = 28;
    }
    slot_index = (s16)slot_limit;

    if (slot_index >= 0) {
        item_category_table = item_category_groups;

        /*
         * BUG: trap rooms overwrite spawn slots, including zero, without checking for existing entries. On
         * floor 31 this can replace the reserved Beldo vision.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        for (; slot_index >= 0; slot_index--) {
            x_offset = random_dungeon_range_16(0, (rect->width - 1) & 0xFFFF) & 0xFFFF;
            y_offset = random_dungeon_range_16(0, (rect->height - 1) & 0xFFFF) & 0xFFFF;
            get_offset_map_cell_value_and_flags((s16)(rect->x + x_offset - 1),
                          (s16)(rect->y + y_offset), 0, &tile_flags);
            if (!(tile_flags & 0x8820)) {
                ((floor_generate_isolated_8028A0F4_DungeonSpot *)dungeon_floor_object_positions)[slot_index].px = (u8)rect->x + x_offset;
                ((floor_generate_isolated_8028A0F4_DungeonSpot *)dungeon_floor_object_positions)[slot_index].py = (u8)rect->y + y_offset;
                if (special_roll == 0) {
                    ((floor_generate_isolated_8028A0F4_DungeonSlot *)floor_objects)[slot_index].kind = 7;
                } else {
                    kind_roll = generate_random_value() & 0xFFFF;
                    item_kind = (kind_roll % 19) + 1;
                    item_flags = *(u16 *)(item_category_table[21].entries +
                                          ((s16)item_kind * 12));
                    stored_kind = item_kind;
                    if ((item_flags & 0x3000) == 0x3000) {
                        continue;
                    }
                    ((floor_generate_isolated_8028A0F4_DungeonSlot *)floor_objects)[slot_index].kind = stored_kind;
                }
                ((floor_generate_isolated_8028A0F4_DungeonSlot *)floor_objects)[slot_index].f1 = 0x15;
                ((floor_generate_isolated_8028A0F4_DungeonSlot *)floor_objects)[slot_index].f3 = 0x80;
                ((floor_generate_isolated_8028A0F4_DungeonSlot *)floor_objects)[slot_index].f2 = 0;
                cycle_map_cell_flags(((floor_generate_isolated_8028A0F4_DungeonSpot *)dungeon_floor_object_positions)[slot_index].px, ((floor_generate_isolated_8028A0F4_DungeonSpot *)dungeon_floor_object_positions)[slot_index].py, TILE_HAS_OBJECT);
            }
        }
    }
}

/* Places random floor items in the room and marks eligible item tiles. */
void mark_random_eligible_region_tiles(floor_generate_isolated_8028A328_S_8001D328_0 *region, s32 unused) {
    s32 random_bits;
    u16 tile_flags;
    s16 count;
    s32 entry_index;
    s32 x_offset;
    s32 y_offset;
    u8 *state;
    u8 *state_prefix;
    floor_generate_isolated_8028A328_S_8001D328_1 *coords;
    s32 sum;
    u8 *state_base;
    u8 *prefix_base;
    s32 state_offset;

    random_bits = generate_random_value();
    sum = ((region->unk_06 * region->unk_04) >> 6) + (random_bits & 7) + 4;
    count = sum;
    if ((s16)sum >= 0x3D) {
        count = 0x3C;
    }
    entry_index = count;
    if (entry_index >= 0) {
        state_base = D_800E3549;
        prefix_base = state_base - 1;
        state_offset = entry_index * 4;
        state_prefix = state_offset + prefix_base;
        state = state_offset + state_base;
        do {
            coords = (floor_generate_isolated_8028A328_S_8001D328_1 *)((u8 *)dungeon_ground_item_positions + entry_index * 0xC);
            x_offset = random_dungeon_range_16(0, (region->unk_04 - 1) & 0xFFFF) & 0xFFFF;
            y_offset = random_dungeon_range_16(0, (region->unk_06 - 1) & 0xFFFF) & 0xFFFF;
            coords->unk_00 = region->unk_00 + x_offset;
            coords->unk_01 = region->unk_02 + y_offset;
            if (((get_offset_map_cell_value_and_flags(coords->unk_00 - 1, coords->unk_01, 0, &tile_flags) << 16) == 0) || !(tile_flags & 0xFF20)) {
                cycle_map_cell_flags(coords->unk_00, coords->unk_01, TILE_HAS_ITEM);
                /*
                 * BUG: item rooms fill the low item slots before ordinary population and skip special
                 * selection here. If every slot below the ordinary item limit is filled, population never calls the
                 * special selector, suppressing the Blue Collar or Healing Herb instead of reserving a slot for it.
                 * Found and documented by the Azure Dreams community (adrando.com/guide/bugs.html).
                 */
                select_floor_item_with_special_overrides(state, state_prefix, 0, 1);
            }
            state_prefix -= 4;
            state -= 4;
            entry_index--;
        } while (entry_index >= 0);
    }
}

/* Rolls for a special room feature or changes tile heights, allowing only one special feature. */
void choose_random_region_feature(Rec_func_8001CE44_arg0 *region, s32 update_id) {
    u32 feature_roll;
    s16 saved_update_id = update_id;

    region->unk_0A = 1;
    feature_roll = generate_random_value() & 0xFF;
    switch (feature_roll) {
    case 0:
        region->unk_0A = 2;
        return;
    case 1:
        if (generation_special_feature_placed != 0) {
            break;
        }
        region->unk_0A = 3;
        generation_special_feature_placed = 1;
        initialize_random_room_slot(region, saved_update_id);
        return;
    case 2:
        if (generation_special_feature_placed != 0) {
            break;
        }
        generation_special_feature_placed = 1;
        region->unk_0A = 2;
        mark_random_eligible_region_tiles(region, saved_update_id);
        return;
    case 4:
        if (generation_special_feature_placed != 0) {
            break;
        }
        generation_special_feature_placed = 1;
        region->unk_0A = 4;
        place_room_trap_records(region, saved_update_id);
        return;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        adjust_random_parity_tile_heights(region, saved_update_id);
    }
    return;
}

/* Fills room terrain, adds random raised or lowered patches, and writes its border. */
void fill_region_with_random_patches(floor_generate_isolated_8028A5D8_DungeonRect *rect, s32 update_id) {
    register u32 value = rect->value;
    s16 left;
    u16 top;
    u16 width;
    u16 height;
    u16 right;
    s16 bottom;
    s16 patch_x;
    s16 patch_y;
    s16 scan_x;
    s16 scan_y;
    s16 cell_x;
    s32 patches_left;
    s16 patch_width;
    s16 patch_height;
    s16 cols_left;
    s16 rows_left;
    s16 signed_width;
    s16 signed_height;
    s32 size_sum;
    s32 patch_count;
    u16 swap_styles;
    s16 patch_style;
    s16 fill_value;
    s32 style_value_hi;
    floor_generate_isolated_8028A5D8_DungeonCell *cell;
    s32 patch_row;
    s32 right_hi;
    u32 col_hi;
    floor_generate_isolated_8028A5D8_DungeonState *state = &(*(floor_generate_isolated_8028A5D8_DungeonState *)scene_geometry);

    left = rect->x;
    top = rect->y;
    width = rect->width;
    height = rect->height;
    right = left + width;
    bottom = top + height;
    fill_value = value - 0x80;
    scan_y = top;

    if ((s16)top < (s16)bottom) {
        for (; (s16)scan_y < (s16)bottom; scan_y++) {
            scan_x = left;
            if (((s32)(s16)left << 16) <
                (right_hi = (s32)(s16)right << 16)) {
                s32 fill_row;
                s32 fill_right;

                fill_row = (s16)scan_y;
                fill_right = right_hi >> 16;

                do {
                    s16 next_x;

                    col_hi = (u32)(u16)scan_x << 16;
                    next_x = scan_x + 1;
                    scan_x = next_x;
                    cell = &((floor_generate_isolated_8028A5D8_DungeonCell *)generation_cells)[
                        (fill_row << state->stride) +
                        ((s32)col_hi >> 16)];
                    cell->kind = 25;
                    cell->value = fill_value;
                    cell->flags = 6;
                } while ((s16)scan_x < fill_right);
            }
        }
    }
    swap_styles = generate_random_value() & 1;
    signed_width = (s16)width;
    signed_height = (s16)height;
    size_sum = signed_width + signed_height;

    if (size_sum < 0) {
        size_sum += 3;
    }
    patch_count = size_sum >> 2;
    {
        floor_generate_isolated_8028A5D8_DungeonPage *level_page = (floor_generate_isolated_8028A5D8_DungeonPage *)resident_globals_page;

        if (level_page->level < 5) {
            patch_count = size_sum >> 4;
        }
    }
    patches_left = patch_count;
    if (patch_count > 0) {
        do {
            patch_x = (s16)left + ((generate_random_value() & 0xFFFF) % signed_width);
            patch_y = (s16)top + ((generate_random_value() & 0xFFFF) % signed_height);
            scan_x = patch_x;
            scan_y = patch_y;
            patch_width = ((signed_width - (patch_x - (s16)left)) / 2 +
                (generate_random_value() & 7)) - 4;
            patch_height = ((signed_height - (patch_y - (s16)top)) / 2 +
                (generate_random_value() & 7)) - 4;
            patch_style = (generate_random_value() & 7) != 0;

            rows_left = patch_height;
            if (patch_height > 0) {
                do {
                    register s32 coord_hi = (s32)scan_y << 16;
                    register s16 coord = coord_hi >> 16;
                    if (coord < (s16)bottom) {
                        cell_x = scan_x;
                        cols_left = patch_width;

                        if (cols_left > 0) {
                            s32 row_style;

                            patch_row = coord;
                            row_style = patch_style;
                            style_value_hi = (value - 0x40) << 16;
                            do {
                                s32 alt_value;
                                floor_generate_isolated_8028A5D8_DungeonCell *patch_cell;
                                coord_hi = (s32)cell_x << 16;
                                coord = coord_hi >> 16;
                                if (coord < (s16)right) {
                                    cell = &((floor_generate_isolated_8028A5D8_DungeonCell *)generation_cells)[(patch_row << state->stride) + coord];
                                    coord = swap_styles;
                                    if (coord != 0) {
                                        patch_cell = cell;
                                        if (row_style != 0) {
                                            advance_generation_step_pair(patch_cell, style_value_hi >> 16);
                                        } else {
                                            alt_value = value - 0xC0;
                                            retreat_generation_step_pair(patch_cell, (s16)alt_value);
                                        }
                                    } else {
                                        patch_cell = cell;
                                        if (row_style != 0) {
                                            alt_value = value - 0xC0;
                                            retreat_generation_step_pair(patch_cell, (s16)alt_value);
                                        } else {
                                            advance_generation_step_pair(patch_cell, style_value_hi >> 16);
                                        }
                                    }
                                }
                                cols_left--;
                                cell_x++;
                            } while (cols_left > 0);
                        }
                    }
                    rows_left--;
                    scan_y++;
                } while (rows_left > 0);
            }
            patches_left--;
        } while (patches_left > 0);
    }
    write_rectangular_border((s16)left, (s16)top, (s16)right, (s16)bottom, (s16)value);
}

/* Writes corner and edge tile kinds, heights, and flags around a rectangle. */
void write_rectangular_border(s16 left_x, s16 top_y, s16 right_x, s16 bottom_y, s32 tile_value_base) {
    s16 *tile;
    s16 *opposite_tile;
    u8 *info_page;
    MapGrid *info;
    s16 tile_value;
    register s16 bottom_row;
    s16 x;
    s16 y;
    info_page = (u8 *)0x80080000;
    info = &g_game_work.map;
    bottom_row = bottom_y;
    tile = (s16 *)(generation_border_cell_base_alias + (((((s16)top_y - 1) << info->shiftX) + left_x) * 6));
    tile[0] = 0xE;
    tile_value = tile_value_base + 0x40;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(generation_border_cell_base_alias + 6 + (((((s16)top_y - 1) << info->shiftX) + right_x) * 6));
    tile[0] = 0xB;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(generation_border_cell_base_alias + ((((bottom_row << info->shiftX) + left_x) * 6)));
    tile[0] = 0xD;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(generation_border_cell_base_alias + 6 + ((((bottom_row << info->shiftX) + right_x) * 6)));
    tile[0] = 0xC;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(generation_border_cell_base_alias + 6 + (((((s16)top_y - 1) << info->shiftX) + left_x) * 6));
    opposite_tile = (s16 *)(generation_border_cell_base_alias + 6 + (((bottom_row << info->shiftX) + left_x) * 6));
    x = left_x;
    if (left_x < right_x) {
        do {
            x++;
            tile[0] = 0x12;
            opposite_tile[0] = 0x10;
            opposite_tile[1] = tile_value;
            tile[1] = tile_value;
            opposite_tile[2] = 9;
            tile[2] = 9;
            tile += 3;
            opposite_tile += 3;
        } while (x < right_x);
    }

    y = top_y;
    tile = (s16 *)(generation_border_cell_base_alias + ((((y << info->shiftX) + left_x) * 6)));
    opposite_tile = (s16 *)(generation_border_cell_base_alias + 6 + ((((y << info->shiftX) + right_x) * 6)));
    if (y < bottom_row) {
        do {
            y++;
            tile[0] = 0x11;
            opposite_tile[0] = 0xF;
            opposite_tile[1] = tile_value;
            tile[1] = tile_value;
            opposite_tile[2] = 9;
            tile[2] = 9;
            tile = (s16 *)((u8 *)tile + (6 << info->shiftX));
            opposite_tile = (s16 *)((u8 *)opposite_tile + (6 << info->shiftX));
        } while (y < bottom_row);
    }
}

/* Deactivates the room and clears its generation cells, including the surrounding margin. */
void clear_region_grid_rectangle(floor_generate_isolated_8028AC34_S_8001DC34_0 *region)
{
    s16 row;
    s16 cells_left;
    s16 *cell;
    u8 *cell_tail;
    MapGrid *grid_config;
    unsigned long grid_base;
    s16 first_row;
    s16 next_row;
    s16 end_row;
    s16 remaining;
    s32 row_width;
    grid_config = &g_game_work.map;
    region->unk_0A = 0;
    first_row = region->unk_02 - 1;
    row = first_row;
    end_row = first_row + region->unk_06 + 2;
    if ((first_row << 16) < (end_row << 16)) {
        grid_base = (unsigned long)generation_border_cell_base_alias;
        do {
            cell = (s16 *)((((row << grid_config->shiftX) +
                  region->unk_00) * 6) + grid_base);
            row_width = region->unk_04 + 2;
            cells_left = row_width;
            if ((row_width << 16) > 0) {
                cell_tail = (u8 *)cell + 4;
                do {
                    remaining = cells_left - 1;
                    cells_left = remaining;
                    *cell = 0;
                    ((floor_generate_isolated_8028AC34_S_8001DC34_1_pre *)cell_tail)[-1].unk_00 = 0;
                    ((floor_generate_isolated_8028AC34_S_8001DC34_1 *)cell_tail)->unk_00 = 0;
                    cell_tail += 6;
                    cell = (s16 *)((u8 *)cell + 6);
                } while ((remaining << 16) > 0);
            }
            next_row = row + 1;
            row = next_row;
        } while (next_row < end_row);
    }
}

/*
 * While the step count is below nine, increments both counters and advances the paired offset by
 * 0x20.
 */
void advance_generation_step_pair(void *step_state, s32 update_id)
{
    if ((*((u16 *) (((u8 *) step_state) + 4))) < 9) {
        *((u16 *) (((u8 *) step_state) + 0)) = (*((u16 *) (((u8 *) step_state) + 0))) + 1;
        *((u16 *) (((u8 *) step_state) + 2)) = (*((u16 *) (((u8 *) step_state) + 2))) + 0x20;
        *((u16 *) (((u8 *) step_state) + 4)) = (*((u16 *) (((u8 *) step_state) + 4))) + 1;
    }
}

/*
 * While the signed step count is positive, decrements both counters and retreats the paired offset
 * by 0x20.
 */
void retreat_generation_step_pair(void *step_state, s32 update_id)
{
    if (((s16 *) step_state)[2] > 0) {
        ((u16 *) step_state)[0] = (u16) (((u16 *) step_state)[0] - 1);
        ((u16 *) step_state)[1] = (u16) (((u16 *) step_state)[1] - 0x20);
        ((u16 *) step_state)[2] = (u16) (((u16 *) step_state)[2] - 1);
    }
}

/* Returns the lowest signed cell value along a sequence of grid coordinates. */
s16 get_minimum_stepped_cell_value(s32 x, s32 y, s32 count, s16 x_step, s16 y_step) {
    s32 remaining = count - 1;
    s16 row_shift = g_game_work.map.shiftX;
    s16 row_step;
    u16 min_value;
    floor_generate_isolated_8028AD84_D_800EA000_Record *record;

    record = &((floor_generate_isolated_8028AD84_D_800EA000_Record *)generation_cells)[((y << row_shift) + x)];
    x += x_step;
    row_step = y_step;
    y += row_step;
    min_value = record->value;
    if (remaining > 0) {
        s16 loop_shift = row_shift;
        do {
            record = &((floor_generate_isolated_8028AD84_D_800EA000_Record *)generation_cells)[((y << loop_shift) + x)];
            if ((s16) record->value < (s16) min_value) {
                min_value = record->value;
            }
            x += x_step;
            remaining -= 1;
            y += row_step;
        } while (remaining > 0);
    }
    return (s16) min_value;
}

/* Adjusts supported terrain tile variants within each active room. */
void update_active_area_tiles(void) {
    floor_generate_isolated_8028AE2C_DungeonArea *area;
    MapGrid *map_config = &g_game_work.map;
    s16 *tile_id;
    s32 area_index;
    s32 x;
    s32 y;
    s32 start_x;
    s32 width;
    s32 height;
    s32 x_end;
    s32 y_end;
    s32 amount_small;
    s32 amount_large;

    area_index = 0;
    amount_small = 0x20;
    amount_large = 0x100;
    area = (floor_generate_isolated_8028AE2C_DungeonArea *)dungeon_rooms;

outer_loop:
    if (area->active != 0) {
        y = area->y;
        start_x = area->x;
        width = area->width;
        height = area->height;
        x_end = start_x + width;
        y_end = y + height;
        for (; y < y_end; y++) {
            x = area->x;
            if (x < x_end) {
x_loop_done:
                tile_id = (s16 *)&((u8 *)generation_cells)[((y << map_config->shiftX) + x) * 6];
                if (is_value_within_inclusive_bounds(*tile_id, 0x13, 0x1C) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x13, amount_small);
                    if ((y & 1) ? (x & 1) : !(x & 1)) {
                        *tile_id += 10;
                    }
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x27, 0x30) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x27, amount_small);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x31, 0x3A) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x31, amount_small);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x3B, 0x44) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x3B, amount_small);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x45, 0x4E) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x45, amount_small);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x6B, 0x6F) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x6B, amount_large);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x70, 0x74) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x70, amount_large);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x75, 0x79) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x75, amount_large);
                } else if (is_value_within_inclusive_bounds(*tile_id, 0x7A, 0x7E) != 0) {
                    empty_dungeon_hook(x, y, tile_id, 0x7A, amount_large);
                }
                x++;
                if (x >= x_end) {
                    continue;
                }
                goto x_loop_done;
            }
        }
    }
    area_index++;
    area++;
    if (area_index >= 0x24) {
        return;
    }
    goto outer_loop;
}

/* Returns without reading or changing state. */
void empty_dungeon_hook(s32 x, s32 y, s16 *tile, s32 kind, s32 amount) { }
