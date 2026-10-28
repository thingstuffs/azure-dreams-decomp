#include "modules/town_map_props.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"


typedef struct S_800BDDD0_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    s16 unk_1A;
} S_800BDDD0_0;

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
    S_800BDDD0_0 *grid;
    s32 cells_addr;

    x = (s16)start_x;
    state = &g_game_work;
    grid = (S_800BDDD0_0 *)((u8 *)state + 0x1DC);
    cells_addr = ((s32)state->map.cells);
    origin_x = start_x;
    end_x = x + 4;
    if (x < end_x) {
        do {
            y = start_y;
            x_limit = end_x;
            while (y < (start_y + 4)) {
                cell_value = (x - origin_x) + 1;
                wrapped_y = y & grid->unk_1A;
                cell_value += (y - start_y) * 4;
                y += 1;
                *((s16 *) (((s32) (((grid->unk_18 & x)
                    + (wrapped_y << grid->unk_14)) << 0x10) >> 0xF) + cells_addr)) = cell_value;
            }
            x += 1;
        } while (x < x_limit);
    }
}
