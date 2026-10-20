#include "dungeon/level/generate.h"

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

