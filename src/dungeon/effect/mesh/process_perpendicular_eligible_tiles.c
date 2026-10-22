#include "common.h"
#include "dungeon/effect/mesh/generation_tile_flags.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"



extern s16 func_800D0FBC(void);
extern s16 func_800D10D0(void);
extern s32 append_coordinate_record(u16, u16, s16, u16);
extern s16 round_sampled_height_to_cell_boundary(s16, s16);

/* Marks and processes up to ten eligible tiles in each perpendicular direction, returning the total. */
s16 process_perpendicular_eligible_tiles(s32 direction, s32 origin_x, s32 origin_y) {
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
