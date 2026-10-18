#include "modules/dungeon_floor_generate.h"

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
    src_room = &D_800E2970[src_idx];
    dest_room = &D_800E2970[dest_idx];
    path_length = 0;
    pick_relative_room_edge_point(src_dir, &src_offset_x, &src_offset_y, src_room);
    pick_relative_room_edge_point((dest_dir + 4) & 6, &dest_offset_x, &dest_offset_y, dest_room);
    travel_dir = src_dir;
    saved_dir = src_dir;
    if (D_800E2970[src_idx].unk_0A) {
        append_generation_region_entry(src_idx, src_room->x + src_offset_x, src_room->y + src_offset_y, 0);
    }
    if (D_800E2970[dest_idx].unk_0A) {
        append_generation_region_entry(dest_idx, dest_room->x + dest_offset_x, dest_room->y + dest_offset_y, 0);
    }
    save_or_restore_random_seed(1);
    start.x = src_room->x + src_offset_x;
    start.y = src_room->y + src_offset_y;
    start.dir = src_dir;
    if (D_800E2970[src_idx].unk_0A) {
        start.x = start.x + dir_step_x[travel_dir];
        start.y = start.y + dir_step_y[travel_dir];
    }
    cursor_x = (s16)(src_idx % D_8001F660) + dir_step_x[travel_dir];
    cursor_y = (s16)(src_idx / D_8001F660) + dir_step_y[travel_dir];
    dest_grid_x = dest_idx % D_8001F660;
    dest_grid_y = dest_idx / D_8001F660;
    for (;;) {
        if (cursor_x == dest_grid_x && cursor_y == dest_grid_y) {
            if (D_800E2970[dest_idx].unk_0A) {
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
        room_idx = cursor_y * D_8001F660 + cursor_x;
        room_marks[room_idx] = 2;
        end.x = D_800E2970[room_idx].x;
        end.y = D_800E2970[room_idx].y;
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
                start.dir = (forward_monster_coordinate_delta(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        } else {
            if (cursor_y == dest_grid_y) {
                start.dir = (forward_monster_coordinate_delta(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
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
    edge_cell = &D_800EA000[(src_y << dungeon->shiftX) + src_x];
    inner_cell = &D_800EA000[((src_y + dir_step_y[back_dir]) << dungeon->shiftX) + src_x + dir_step_x[back_dir]];
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
    edge_cell = &D_800EA000[(cursor_y << dungeon->shiftX) + cursor_x];
    inner_cell = &D_800EA000[((cursor_y + dir_step_y[back_dir]) << dungeon->shiftX) + cursor_x + dir_step_x[back_dir]];
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

    if (D_800E2970[dest_idx].unk_0A) {
        back_dir = dest_dir;
        cursor_x = dest_x;
        cursor_y = dest_y;
        edge_cell = &D_800EA000[(cursor_y << dungeon->shiftX) + cursor_x];
        cursor_x = cursor_x + dir_step_x[dest_dir];
        cursor_y = cursor_y + dir_step_y[dest_dir];
        inner_cell = &D_800EA000[(cursor_y << dungeon->shiftX) + cursor_x];
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
        edge_cell = &D_800EA000[(cursor_y << dungeon->shiftX) + cursor_x];
        inner_cell = &D_800EA000[((cursor_y + dir_step_y[back_dir]) << dungeon->shiftX) + cursor_x + dir_step_x[back_dir]];
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
    if (D_800E2970[src_idx].unk_0A) {
        src_height = D_800EA000[((src_room->y + src_offset_y) << dungeon->shiftX) + src_room->x + src_offset_x].value;
    } else {
        src_height = D_800EA000[(src_room->y << dungeon->shiftX) + src_room->x].value;
    }
    if (D_800E2970[dest_idx].unk_0A) {
        dest_height = D_800EA000[((dest_room->y + dest_offset_y) << dungeon->shiftX) + dest_room->x
            + dest_offset_x].value;
    } else {
        dest_height = D_800EA000[(dest_room->y << dungeon->shiftX) + dest_room->x].value;
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
    if (D_800E2970[src_idx].unk_0A) {
        start.x = start.x + dir_step_x[travel_dir];
        start.y = start.y + dir_step_y[travel_dir];
    }
    cursor_x = (s16)(src_idx % D_8001F660) + dir_step_x[travel_dir];
    cursor_y = (s16)(src_idx / D_8001F660) + dir_step_y[travel_dir];
    dest_grid_x = dest_idx % D_8001F660;
    dest_grid_y = dest_idx / D_8001F660;
    for (;;) {
        if (cursor_x == dest_grid_x && cursor_y == dest_grid_y) {
            if (D_800E2970[dest_idx].unk_0A) {
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
        room_idx = cursor_y * D_8001F660 + cursor_x;
        room_marks[room_idx] = 2;
        end.x = D_800E2970[room_idx].x;
        end.y = D_800E2970[room_idx].y;
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
                start.dir = (forward_monster_coordinate_delta(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        } else {
            if (cursor_y == dest_grid_y) {
                start.dir = (forward_monster_coordinate_delta(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        }
        cursor_x = cursor_x + dir_step_x[start.dir];
        cursor_y = cursor_y + dir_step_y[start.dir];
        travel_dir = start.dir;
    }
    return 0;
}
