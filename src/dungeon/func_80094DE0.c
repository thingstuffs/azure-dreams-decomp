#include "modules/dungeon_engine_tile_map_abi_views.h"
extern s16 D_800DCEBC[];
extern s16 D_800DCEAC[];
#include "common.h"

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);



/* Checks the sides of a diagonal direction for terrain above 0x200. */
s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height)
{
    s32 tile_flags;
    s32 side;
    u32 dir;
    s16 saved;
    s16 h;
    s32 x;
    s32 y;

    saved = direction;
    h = height;
    if (direction & 1) {
        x = tile_x;
        y = tile_y;
        for (side = -1; side < 2; side += 2) {
            if (get_offset_map_cell_value_and_flags(x, y, (saved + side) & 7, &tile_flags) != 0) {
                dir = ((u16)saved + side) & 7;
                if (map_height_wrapped((x << 6) + 0x20 + ((u16 *)D_800DCEAC)[dir], (y << 6) + 0x20 + ((u16 *)D_800DCEBC)[dir], h) > 0x200) {
                    break;
                }
            }
        }
        if (side < 2) {
            return 0;
        }
    }
    return 1;
}
