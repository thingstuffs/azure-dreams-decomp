#include "common.h"

extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_800BCB04();
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

/* Checks whether the selected neighbor has a sampled height above 512 when enabled. */
s32 func_800A4688(s32 world_x, s32 world_y, s32 world_z, u32 direction, s32 disabled) {
    u16 tile_value;
    u16 x_offset;
    u16 y_offset;
    register u32 tile_x ASM_REG("$19");
    register u32 tile_y ASM_REG("$18");
    u32 shifted_sector;
    s32 sector_arg;
    s32 call_x;
    s32 call_y;
    s32 sector;
    s32 height;
    s32 sample_z;
    s32 neighbor_x;
    s32 neighbor_y;
    register s32 result;

    tile_x = (u32)(world_x & 0xFFFF) >> 6;
    tile_y = (u32)(world_y & 0xFFFF) >> 6;
    shifted_sector = direction >> 9;
    sector_arg = shifted_sector & 7;

    if (disabled != 0) {
        return 0;
    }
    ASM_KEEP(tile_x);
    ASM_KEEP(tile_y);
    call_x = tile_x;
    call_y = tile_y;
    ASM_KEEP(call_x);
    ASM_KEEP(call_y);
    sector = sector_arg;
    ASM_KEEP(sector);
    if ((func_8009A350(call_x, call_y, sector_arg, &tile_value) << 16) == 0) {
        return 0;
    }

    sample_z = (s16)(world_z - 0x20);
    x_offset = D_8006CCD8[sector];
    y_offset = D_8006CCE8[sector];
    neighbor_x = x_offset + tile_x;
    neighbor_y = y_offset + tile_y;
    ASM_USE2(neighbor_x, neighbor_y);
    height = func_800BCB04(
        ((((neighbor_x) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        ((((neighbor_y) & 0xFFFF) << 6) + 0x20) & 0xFFE0,
        sample_z);
    result = 0x02000000 < (height << 16);
    tile_value = height;
    return result;
}
