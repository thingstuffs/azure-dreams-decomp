/* Map cell read and its file-private helper. */
#include "common.h"
#include "shared/game_work.h"
typedef struct S_8008E94C_Sub {
    s32 f0;
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

static s32 map_cell_address_at_tile(s32 tile_x, s32 tile_y)
{
    S_80083160_View *map_state = ((S_80083160_View *)&g_game_work);
    S_8008E94C_Sub *map_layout = &map_state->sub;
    s32 tile_index;

    tile_index = (map_layout->mask1 & tile_x) + ((s16)(map_layout->mask2 & tile_y) << map_layout->shift);
    return map_state->sub.f0 + ((tile_index << 0x10) >> 0xF);
}

void town_map_mod_read_p(s16 world_x, s16 world_y) {
    s32 tile_x;
    s32 tile_y;

    tile_x = (s16)world_x;
    if (tile_x < 0) {
        tile_x += 0x3F;
    }
    tile_y = (s16)world_y;
    tile_x >>= 6;
    map_cell_address_at_tile(tile_x, (tile_y / 64));
}
