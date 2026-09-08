#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} Pos;

typedef struct {
    s16 unused[10];
    s16 stride;
} DungeonState;

typedef struct {
    s16 kind;
    s16 value;
    u16 flags;
} DungeonCell;

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
    u8 pad08[2];
    s16 active;
    u8 pad0C[8];
} Room;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern s32 D_8001F660;
extern DungeonState D_8008333C;
extern Room D_800E2970[];
extern DungeonCell D_800EA000[];

extern void func_800177D8(s16, s16, s16, s32);
extern void func_800A6D60(s32);
extern u32 func_800A07D0(s16, s16, s16, s16);
extern void func_8001CCEC(s16, s16 *, s16 *, Room *);
extern s16 func_8001C06C(Pos *, Pos *, s16, s16 *, s16 *);
extern s16 func_8001C5E4(Pos *, Pos *, s16, s16 *, s16 *, s32 *, s32 *);
extern s32 func_8001CE14(s16, s32, s16);

/* Connects rooms with a two-cell-wide corridor and interpolates its floor heights. */
s32 func_8001AC4C(s16 src_dir, s16 dest_dir, s16 src_idx, s16 dest_idx, u8 *room_marks) {
    Pos start;
    Pos end;
    Pos side_start;
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
    Room *src_room;
    s16 path_length;
    s16 saved_dir;
    Room *dest_room;
    DungeonState *dungeon;
    DungeonCell *edge_cell;
    DungeonCell *inner_cell;
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

    dungeon = &D_8008333C;
    src_room = &D_800E2970[src_idx];
    dest_room = &D_800E2970[dest_idx];
    path_length = 0;
    func_8001CCEC(src_dir, &src_offset_x, &src_offset_y, src_room);
    func_8001CCEC((dest_dir + 4) & 6, &dest_offset_x, &dest_offset_y, dest_room);
    travel_dir = src_dir;
    saved_dir = src_dir;
    if (D_800E2970[src_idx].active) {
        func_800177D8(src_idx, src_room->x + src_offset_x, src_room->y + src_offset_y, 0);
    }
    if (D_800E2970[dest_idx].active) {
        func_800177D8(dest_idx, dest_room->x + dest_offset_x, dest_room->y + dest_offset_y, 0);
    }
    func_800A6D60(1);
    start.x = src_room->x + src_offset_x;
    start.y = src_room->y + src_offset_y;
    start.dir = src_dir;
    if (D_800E2970[src_idx].active) {
        start.x = start.x + D_8006CCD8[travel_dir];
        start.y = start.y + D_8006CCE8[travel_dir];
    }
    cursor_x = (s16)(src_idx % D_8001F660) + D_8006CCD8[travel_dir];
    cursor_y = (s16)(src_idx / D_8001F660) + D_8006CCE8[travel_dir];
    dest_grid_x = dest_idx % D_8001F660;
    dest_grid_y = dest_idx / D_8001F660;
    for (;;) {
        if (cursor_x == dest_grid_x && cursor_y == dest_grid_y) {
            if (D_800E2970[dest_idx].active) {
                end.x = dest_room->x + dest_offset_x;
                end.y = dest_room->y + dest_offset_y;
            } else {
                end.x = dest_room->x;
                end.y = dest_room->y;
            }
            end.x = end.x - D_8006CCD8[dest_dir];
            end.y = end.y - D_8006CCE8[dest_dir];
            path_length += func_8001C06C(&start, &end, 1, &join_x, &join_y);
            start.x = start.x + D_8006CCD8[(travel_dir + 2) & 7];
            start.y = start.y + D_8006CCE8[(travel_dir + 2) & 7];
            end.x = end.x + D_8006CCD8[(dest_dir + 2) & 7];
            end.y = end.y + D_8006CCE8[(dest_dir + 2) & 7];
            join_x = join_x - D_8006CCD8[travel_dir];
            join_y = join_y - D_8006CCE8[travel_dir];
            func_8001C06C(&start, &end, 0, &join_x, &join_y);
            break;
        }
        room_idx = cursor_y * D_8001F660 + cursor_x;
        room_marks[room_idx] = 2;
        end.x = D_800E2970[room_idx].x;
        end.y = D_800E2970[room_idx].y;
        path_length += func_8001C06C(&start, &end, 1, &join_x, &join_y);
        side_start = start;
        side_start.x = side_start.x + D_8006CCD8[(travel_dir + 2) & 7];
        side_start.y = side_start.y + D_8006CCE8[(travel_dir + 2) & 7];
        join_x = join_x - D_8006CCD8[travel_dir];
        join_y = join_y - D_8006CCE8[travel_dir];
        func_8001C06C(&side_start, &end, 0, &join_x, &join_y);
        start.x = end.x;
        start.y = end.y;
        if (D_8006CCD8[travel_dir] != 0) {
            if (cursor_x == dest_grid_x) {
                start.dir = (func_800A07D0(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        } else {
            if (cursor_y == dest_grid_y) {
                start.dir = (func_800A07D0(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        }
        cursor_x = cursor_x + D_8006CCD8[start.dir];
        cursor_y = cursor_y + D_8006CCE8[start.dir];
        travel_dir = start.dir;
    }

    travel_dir = saved_dir;
    back_dir = (travel_dir + 4) & 7;
    src_x = src_room->x + src_offset_x;
    src_y = src_room->y + src_offset_y;
    edge_cell = &D_800EA000[(src_y << dungeon->stride) + src_x];
    inner_cell = &D_800EA000[((src_y + D_8006CCE8[back_dir]) << dungeon->stride) + src_x + D_8006CCD8[back_dir]];
    dest_x = dest_room->x + dest_offset_x;
    dest_y = dest_room->y + dest_offset_y;
    if (func_8001CE14(edge_cell->kind, 15, 18)) {
        edge_cell->kind = (inner_cell->flags >> 1) + (travel_dir / 2) * 5 + 79;
        edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
        if (func_8001CE14(inner_cell->kind, 99, 103)) {
            edge_cell->value = edge_cell->value + 96;
        }
    }
    if (func_8001CE14(inner_cell->kind, 19, 28)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
    } else if (func_8001CE14(inner_cell->kind, 99, 103)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
        inner_cell->value = inner_cell->value + 96;
    }

    cursor_x = src_x + D_8006CCD8[(travel_dir + 2) & 7];
    cursor_y = src_y + D_8006CCE8[(travel_dir + 2) & 7];
    edge_cell = &D_800EA000[(cursor_y << dungeon->stride) + cursor_x];
    inner_cell = &D_800EA000[((cursor_y + D_8006CCE8[back_dir]) << dungeon->stride) + cursor_x + D_8006CCD8[back_dir]];
    if (func_8001CE14(edge_cell->kind, 15, 18)) {
        edge_cell->kind = (inner_cell->flags >> 1) + (travel_dir / 2) * 5 + 79;
        edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
        if (func_8001CE14(inner_cell->kind, 99, 103)) {
            edge_cell->value = edge_cell->value + 96;
        }
    }
    if (func_8001CE14(inner_cell->kind, 19, 28)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
    } else if (func_8001CE14(inner_cell->kind, 99, 103)) {
        inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
        inner_cell->value = inner_cell->value + 96;
    }

    if (D_800E2970[dest_idx].active) {
        back_dir = dest_dir;
        cursor_x = dest_x;
        cursor_y = dest_y;
        edge_cell = &D_800EA000[(cursor_y << dungeon->stride) + cursor_x];
        cursor_x = cursor_x + D_8006CCD8[dest_dir];
        cursor_y = cursor_y + D_8006CCE8[dest_dir];
        inner_cell = &D_800EA000[(cursor_y << dungeon->stride) + cursor_x];
        entry_dir = (dest_dir + 4) & 6;
        if (func_8001CE14(edge_cell->kind, 15, 18)) {
            edge_cell->kind = (inner_cell->flags >> 1) + (entry_dir / 2) * 5 + 79;
            edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
            if (func_8001CE14(inner_cell->kind, 99, 103)) {
                edge_cell->value = edge_cell->value + 96;
            }
        }
        if (func_8001CE14(inner_cell->kind, 19, 28)) {
            inner_cell->kind = inner_cell->flags + (entry_dir / 2) * 10 + 39;
        } else if (func_8001CE14(inner_cell->kind, 99, 103)) {
            inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
            inner_cell->value = inner_cell->value + 96;
        }

        cursor_x = dest_x + D_8006CCD8[(entry_dir - 2) & 7];
        cursor_y = dest_y + D_8006CCE8[(entry_dir - 2) & 7];
        edge_cell = &D_800EA000[(cursor_y << dungeon->stride) + cursor_x];
        inner_cell = &D_800EA000[((cursor_y + D_8006CCE8[back_dir]) << dungeon->stride) + cursor_x + D_8006CCD8[back_dir]];
        if (func_8001CE14(edge_cell->kind, 15, 18)) {
            edge_cell->kind = (inner_cell->flags >> 1) + (entry_dir / 2) * 5 + 79;
            edge_cell->value = inner_cell->value - ((inner_cell->flags & 1) << 5);
            if (func_8001CE14(inner_cell->kind, 99, 103)) {
                edge_cell->value = edge_cell->value + 96;
            }
        }
        if (func_8001CE14(inner_cell->kind, 19, 28)) {
            inner_cell->kind = inner_cell->flags + (entry_dir / 2) * 10 + 39;
        } else if (func_8001CE14(inner_cell->kind, 99, 103)) {
            inner_cell->kind = inner_cell->flags + (travel_dir / 2) * 10 + 39;
            inner_cell->value = inner_cell->value + 96;
        }
    }

    func_800A6D60(0);
    travel_dir = saved_dir;
    if (D_800E2970[src_idx].active) {
        src_height = D_800EA000[((src_room->y + src_offset_y) << dungeon->stride) + src_room->x + src_offset_x].value;
    } else {
        src_height = D_800EA000[(src_room->y << dungeon->stride) + src_room->x].value;
    }
    if (D_800E2970[dest_idx].active) {
        dest_height = D_800EA000[((dest_room->y + dest_offset_y) << dungeon->stride) + dest_room->x + dest_offset_x].value;
    } else {
        dest_height = D_800EA000[(dest_room->y << dungeon->stride) + dest_room->x].value;
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
    if (D_800E2970[src_idx].active) {
        start.x = start.x + D_8006CCD8[travel_dir];
        start.y = start.y + D_8006CCE8[travel_dir];
    }
    cursor_x = (s16)(src_idx % D_8001F660) + D_8006CCD8[travel_dir];
    cursor_y = (s16)(src_idx / D_8001F660) + D_8006CCE8[travel_dir];
    dest_grid_x = dest_idx % D_8001F660;
    dest_grid_y = dest_idx / D_8001F660;
    for (;;) {
        if (cursor_x == dest_grid_x && cursor_y == dest_grid_y) {
            if (D_800E2970[dest_idx].active) {
                end.x = dest_room->x + dest_offset_x;
                end.y = dest_room->y + dest_offset_y;
            } else {
                end.x = dest_room->x;
                end.y = dest_room->y;
            }
            end.x = end.x - D_8006CCD8[dest_dir];
            end.y = end.y - D_8006CCE8[dest_dir];
            if (func_8001C5E4(&start, &end, 1, &join_x, &join_y, main_height, height_step) < 0) {
                goto failed;
            }
            start.x = start.x + D_8006CCD8[(travel_dir + 2) & 7];
            start.y = start.y + D_8006CCE8[(travel_dir + 2) & 7];
            end.x = end.x + D_8006CCD8[(dest_dir + 2) & 7];
            end.y = end.y + D_8006CCE8[(dest_dir + 2) & 7];
            join_x = join_x - D_8006CCD8[travel_dir];
            join_y = join_y - D_8006CCE8[travel_dir];
            if (func_8001C5E4(&start, &end, 0, &join_x, &join_y, side_height, height_step) < 0) {
                goto failed;
            }
            break;
        }
        room_idx = cursor_y * D_8001F660 + cursor_x;
        room_marks[room_idx] = 2;
        end.x = D_800E2970[room_idx].x;
        end.y = D_800E2970[room_idx].y;
        if (func_8001C5E4(&start, &end, 1, &join_x, &join_y, main_height, height_step) < 0) {
            goto failed;
        }
        side_start = start;
        side_start.x = side_start.x + D_8006CCD8[(travel_dir + 2) & 7];
        side_start.y = side_start.y + D_8006CCE8[(travel_dir + 2) & 7];
        join_x = join_x - D_8006CCD8[travel_dir];
        join_y = join_y - D_8006CCE8[travel_dir];
        if (func_8001C5E4(&side_start, &end, 0, &join_x, &join_y, side_height, height_step) < 0) {
            goto failed;
        }
        start.x = end.x;
        start.y = end.y;
        if (D_8006CCD8[travel_dir] != 0) {
            if (cursor_x == dest_grid_x) {
                start.dir = (func_800A07D0(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        } else {
            if (cursor_y == dest_grid_y) {
                start.dir = (func_800A07D0(cursor_x, cursor_y, dest_grid_x, dest_grid_y) >> 9) & 6;
            }
        }
        cursor_x = cursor_x + D_8006CCD8[start.dir];
        cursor_y = cursor_y + D_8006CCE8[start.dir];
        travel_dir = start.dir;
    }
    return 0;
}
