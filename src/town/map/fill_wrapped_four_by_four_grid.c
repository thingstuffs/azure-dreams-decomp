#include "modules/town_map_props.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "town/map.h"


/* Writes values 1 through 16 in row order into a wrapped 4x4 grid region. */
void fill_wrapped_four_by_four_grid(s32 start_x, s16 start_y, s32 unused_value) {
    s16 cell_value;
    s32 y;
    s32 x;
    s32 end_x;
    s32 wrapped_y;
    s32 origin_x;
    s32 x_limit;
    GameWork *state;
    MapGrid *grid;
    s32 cells_addr;

    x = (s16)start_x;
    state = &g_game_work;
    grid = &state->map;
    cells_addr = ((s32)state->map.cells);
    origin_x = start_x;
    end_x = x + 4;
    if (x < end_x) {
        do {
            y = start_y;
            x_limit = end_x;
            while (y < (start_y + 4)) {
                cell_value = (x - origin_x) + 1;
                wrapped_y = y & grid->maskY;
                cell_value += (y - start_y) * 4;
                y += 1;
                *((s16 *) (((s32) ((((u16)grid->maskX & x)
                    + (wrapped_y << grid->shiftX)) << 0x10) >> 0xF) + cells_addr)) = cell_value;
            }
            x += 1;
        } while (x < x_limit);
    }
}
