/* Directional tile flag processing
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00301 - CL:dungeon/func_800CB680, CL:dungeon/func_800CB9CC, CL:dungeon/func_800CBBD8, CL:dungeon/func_800CBF3C, CL:dungeon/func_800CBFFC.
 * CL:dungeon/func_800CB680
 * CL:dungeon/func_800CB9CC
 * CL:dungeon/func_800CBBD8
 * CL:dungeon/func_800CBF3C
 * CL:dungeon/func_800CBFFC
 */
#include "dungeon/effect/mesh.h"

/* Private declarations retained from the member sources. */
/* Directional tile flag processing */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00301 - CL:dungeon/func_800CB680, CL:dungeon/func_800CB9CC, CL:dungeon/func_800CBBD8, CL:dungeon/func_800CBF3C, CL:dungeon/func_800CBFFC. */

#include "common.h"
#include "dungeon/effect/mesh/generation_tile_flags.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

#include "m2c_compat.h"
#include "engine/effect.h"

typedef struct S_800D13B8_1 {
    u8 pad_00[0xA4];
    u16 unk_A4;
    u16 unk_A6;
} S_800D13B8_1;

extern s16 func_800D0FBC(void);
extern s16 func_800D10D0(void);
extern void append_coordinate_record(s32 x, s32 y, s32 value, s32 store_value);
extern s16 round_sampled_height_to_cell_boundary(s32 grid_x, s32 grid_y);
extern s32 get_offset_map_cell_value_and_flags(s16, s16, s16, u16 *);
extern s16 sound_idle_vsync_frame_alias[8];
extern u8 D_800E6000[16400];
extern u8 *tile_coordinate_records;

/* Marks and processes up to ten eligible tiles in each perpendicular direction, returning the total. */
s16 process_perpendicular_eligible_tiles(s16 direction, s16 origin_x, s16 origin_y) {
    register MapGrid *settings = &g_game_work.map;
    s16 second_stopped = 0;
    s16 first_stopped = 0;
    s16 plus_dir = (direction + 2) & 7;
    s16 minus_dir = (direction - 2) & 7;
    u16 first_count;
    u16 second_count;
    s16 first_x = dir_step_x[(s16)direction] + origin_x;
    s16 first_y = dir_step_y[(s16)direction] + origin_y;
    s16 second_x = dir_step_x[minus_dir] + first_x;
    s16 second_y = dir_step_y[minus_dir] + first_y;
    register s32 step = 0;

    first_count = second_count = 0;

    do {
        if (first_x < 0 || first_x >= (1 << settings->shiftX)) {
            first_stopped = 1;
        }
        if (first_y < 0 || first_y >= (1 << settings->shiftY)) {
            first_stopped = 1;
        }
        if (!first_stopped) {
            DungeonTile *tile = &generation_cells[first_x + (first_y << settings->shiftX)];
            if (tile->flags & 4) {
                first_count++;
                tile->flags |= 0x80;
                append_coordinate_record((u16)first_x, (u16)first_y,
                              round_sampled_height_to_cell_boundary(first_x, first_y),
                              tile->flags & 8);
                first_x += dir_step_x[plus_dir];
                first_y += dir_step_y[plus_dir];
            } else {
                first_stopped = 1;
            }
        }

        if (second_x < 0 || second_x >= (1 << settings->shiftX)) {
            second_stopped = 1;
        }
        if (second_y < 0 || second_y >= (1 << settings->shiftY)) {
            second_stopped = 1;
        }
        if (!second_stopped) {
            DungeonTile *tile = &generation_cells[second_x + (second_y << settings->shiftX)];
            if (tile->flags & 4) {
                second_count++;
                tile->flags |= 0x80;
                append_coordinate_record((u16)second_x, (u16)second_y,
                              round_sampled_height_to_cell_boundary(second_x, second_y),
                              tile->flags & 8);
                second_x += dir_step_x[minus_dir];
                second_y += dir_step_y[minus_dir];
            } else {
                second_stopped = 1;
            }
        }
    } while (++step < 10);

    return first_count + second_count;
}

/* Counts flagged tiles along a direction for up to eleven steps. */
s32 count_flagged_tiles_along_direction_2(s16 scan_direction, s32 start_x, s32 start_y) {
    s32 bound_bit;
    u16 flags;
    s32 saved_offset;
    u16 *saved_x_step;
    u16 *y_step;
    s32 direction;
    register s32 byte_offset;
    u8 *x_base;
    u16 *x_step;
    MapGrid *bounds;
    s16 x_acc;
    s16 y_acc;
    s16 x;
    s16 y;
    s32 remaining;
    s32 count;

    remaining = 11;
    direction = scan_direction;
    x_base = (u8 *)dir_step_x;
    byte_offset = direction * 2;
    x_step = (u16 *)(x_base + byte_offset);
    count = 0;
    x_acc = start_x - *x_step;
    x = (u16)x_acc;
    bounds = &g_game_work.map;

    if (x < 0 || x >= ((bound_bit = 1) << bounds->shiftX)) {
        return 0;
    }

    {
        u8 *y_base;

        y_base = (u8 *)dir_step_y;
        y_step = (u16 *)(y_base + byte_offset);
        y_acc = start_y - *y_step;
    }
    y = (s16)y_acc;
    if (y < 0) {
        return 0;
    }
    if (y >= (bound_bit << bounds->shiftY)) {
        return 0;
    }

    saved_offset = byte_offset;
    saved_x_step = x_step;
    do {
        u16 *loop_x_step;
        x = (s16)x_acc;
        y = (s16)y_acc;
        if ((get_offset_map_cell_value_and_flags(x, y, direction, &flags) << 16) != 0 &&
            (flags & 4)) {
            count++;
            if (process_perpendicular_eligible_tiles(direction, x, y) >= 2) {
                break;
            }
        }

        {
            loop_x_step = saved_x_step;
            x_acc += *loop_x_step;
        }
        x = (s16)x_acc;
        if (x < 0 || x >= (1 << bounds->shiftX)) {
            break;
        }

        {
            u8 *loop_y_base;

            loop_y_base = (u8 *)dir_step_y;
            loop_x_step = (u16 *)(saved_offset);
            loop_y_base += (s32)loop_x_step;
            y_step = (u16 *)loop_y_base;
            y_acc += *y_step;
        }
        y = (s16)y_acc;
        if (y < 0 || y >= (1 << bounds->shiftY)) {
            break;
        }
    } while (--remaining > 0);

    return (s16)count;
}

/* Clear flag 0x80 on the listed tiles and reset the list. */
void clear_listed_tile_flags(void) {
    u8 *entry;
    u8 *tile;
    u16 tile_flags;
    MapGrid *map_config;

    map_config = &g_game_work.map;
    entry = tile_coordinate_records;
    if (*entry != 0) {
        do {
            tile = &D_800E6000[0x4000 + (entry[0] + (entry[1] << map_config->shiftX)) * 6];
            tile_flags = *(u16 *)(tile + 4);
            entry += 4;
            *(s16 *)(tile + 4) = (s16)(tile_flags & 0xFF7F);
        } while (*entry != 0);
    }
    *(s16 *)((u8 *)sound_idle_vsync_frame_alias + 4) = 0;
    *tile_coordinate_records = 0;
}

/* Processes directions around the current position based on the facing angle. */
void process_current_facing_directions(void) {
    GameWork *state;
    S_800D13B8_1 *direction_work;
    s32 next_axis_direction;
    s32 axis_index = 0;
    u16 *y_step;
    s16 coord_x;
    s16 coord_y;
    s32 facing;
    s32 direction;
    s32 diagonal_x;
    s16 diagonal_y;
    s32 next_direction;
    s32 offset_x_high;
    s32 last_direction;
    s32 last_x;
    s32 last_y;
    s32 last_x_high;
    s32 last_y_high;
    s32 axis_step;
    u16 *x_step;
    u16 *diagonal_x_step;

    state = &g_game_work;
    direction_work = (S_800D13B8_1 *)((u8 *)state + 0x18);
    if (runtime_update_saved_vectors() != 0) {
        facing = 2 - ((s32) (state->view.camera_rotation.parts.viewAngle + 0x100) >> 9);
        clear_listed_tile_flags();
        coord_x = (u16) direction_work->unk_A4 >> 6;
        coord_y = (u16) direction_work->unk_A6 >> 6;
        direction = facing & 7;
        if (facing & 1) {
            diagonal_x = coord_x;
            diagonal_y = coord_y;
            count_flagged_tiles_along_direction_2((direction + 1) & 7, diagonal_x, diagonal_y);
            count_flagged_tiles_along_direction_2((direction - 1) & 7, diagonal_x, diagonal_y);
            next_direction = direction + 3;
            next_direction &= 7;
            diagonal_x_step = dir_step_x;
            diagonal_x_step = &diagonal_x_step[direction];
            count_flagged_tiles_along_direction_2(next_direction, (u32) (s16) (diagonal_x + ((s16) *diagonal_x_step * 0xA)),
                (u32) (s16) (diagonal_y + ((s16) dir_step_y[direction] * 0xA)));
            last_direction = (direction - 3) & 7;
            last_x = (s16) (diagonal_x + ((s16) *diagonal_x_step * 0xA));
            last_y = (s16) (diagonal_y + ((s16) dir_step_y[direction] * 0xA));
            count_flagged_tiles_along_direction_2(last_direction, last_x, last_y);
        } else {
            axis_index = direction;
            count_flagged_tiles_along_direction_2(axis_index, coord_x, coord_y);
            next_axis_direction = axis_index + 2;
            next_axis_direction &= 7;
            count_flagged_tiles_along_direction_2(next_axis_direction, coord_x, coord_y);
            last_direction = axis_index - 2;
            last_direction &= 7;
            count_flagged_tiles_along_direction_2(last_direction, coord_x, coord_y);
            next_direction = axis_index + 4;
            next_direction &= 7;
            x_step = dir_step_x;
            axis_index *= 2;
            x_step = (u16 *) ((s8 *) x_step + axis_index);
            offset_x_high = (s32) ((u32) (coord_x + ((s16) *x_step * 0xA)) << 16);
            y_step = (u16 *)((s8 *)dir_step_y + axis_index);
            count_flagged_tiles_along_direction_2(next_direction, offset_x_high >> 16, (u32) (s16) (coord_y
                + ((s16) *y_step * 0xA)));
            count_flagged_tiles_along_direction_2(next_axis_direction, (u32) (s16) (coord_x + ((s16) *x_step * 0xA)),
                (u32) (s16) (coord_y + ((s16) *y_step * 0xA)));
            last_x_high = (s32)((u32)(coord_x + (s16)*x_step * 0xA) << 16);
            axis_step = (s16) *y_step;
            last_x = last_x_high >> 16;
            last_y_high = (s32) ((u32) (coord_y + (axis_step * 0xA)) << 16);
            last_y = last_y_high >> 16;
            count_flagged_tiles_along_direction_2(last_direction, last_x, last_y);
        }
    }
}
