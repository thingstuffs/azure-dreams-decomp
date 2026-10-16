#include "modules/dungeon_floor_generate.h"

s32 dungeonClassifyDirectionalMovement(s16 input_x, s16 input_y, s32 current_height, s16 direction)
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
    if ((dungeonCheckDiagonalSideHeight(direction & 0xFFFF, tile_x, tile_y, probe_height) << 16) == 0) {
        return 0;
    }

    if ((getOffsetMapCellValueAndFlags(tile_x, tile_y, direction, &tile_flags) << 16) == 0) {
        return 0;
    }

    next_x = input_x + dirStepX[direction];
    next_y = input_y + dirStepY[direction];
    if (tile_flags & 0x8400) {
        return 0;
    }

    target_height = func_800BCB04(
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

