#include "common.h"
#include "shared/game_work.h"

typedef struct S_8008E94C_Sub {
    s16 *cells;
    u8 pad4[0x10];
    s16 shift;
    u16 pad16;
    u16 mask1;
    u16 mask2;
} S_8008E94C_Sub;

typedef struct S_80083160_View {
    u8 pad0[0x1DC];
    S_8008E94C_Sub sub;
} S_80083160_View;


/* Return the map cell at the masked tile coordinates. */
s16 *map_cell_address_at_tile(s32 tile_x, s32 tile_y)
{
    S_80083160_View *map_state = ((S_80083160_View *)&g_game_work);
    S_8008E94C_Sub *map_layout = &map_state->sub;
    s32 tile_index;
    s16 cell_index;

    tile_index = (map_layout->mask1 & tile_x) + ((s16)(map_layout->mask2 & tile_y) << map_layout->shift);
    cell_index = tile_index;
    return map_state->sub.cells + cell_index;
}
