#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "dungeon/effect/mesh.h"
#include "engine/effect.h"


typedef struct S_800D13B8_1 {
    u8 pad_00[0xA4];
    u16 unk_A4;
    u16 unk_A6;
} S_800D13B8_1;

/* Processes directions around the current position based on the facing angle. */
void process_current_facing_directions(void) {
    GameWork *state;
    s8 *direction_work;
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
    direction_work = (u8 *)state + 0x18;
    if (runtime_update_saved_vectors() != 0) {
        facing = 2 - ((s32) (state->view.camera_rotation.parts.viewAngle + 0x100) >> 9);
        clear_listed_tile_flags();
        coord_x = (u16) ((S_800D13B8_1 *)direction_work)->unk_A4 >> 6;
        coord_y = (u16) ((S_800D13B8_1 *)direction_work)->unk_A6 >> 6;
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
