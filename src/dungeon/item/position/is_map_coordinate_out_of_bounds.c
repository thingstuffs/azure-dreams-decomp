#include "common.h"
#include "shared/game_work.h"
#include "dungeon/item/position.h"


/* Return whether the coordinates are outside the dungeon bounds. */
s32 is_map_coordinate_out_of_bounds(s16 x, s16 y)
{
    MapGrid *bounds = &g_game_work.map;

    if (x < 0 || x >= (1 << bounds->shiftX)) {
        return 1;
    }
    if (y < 0 || y >= (1 << bounds->shiftY)) {
        return 1;
    }
    return 0;
}
