#include "common.h"

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

extern S_80083160_View D_80083160;

/* Compute the map entry address from masked tile coordinates. */
s32 func_8008C0AC(s32 tile_x, s32 tile_y)
{
    S_80083160_View *map_state = &D_80083160;
    S_8008E94C_Sub *map_layout = &map_state->sub;
    s32 tile_index;

    tile_index = (map_layout->mask1 & tile_x) + ((s16)(map_layout->mask2 & tile_y) << map_layout->shift);
    return map_state->sub.f0 + ((tile_index << 0x10) >> 0xF);
}
