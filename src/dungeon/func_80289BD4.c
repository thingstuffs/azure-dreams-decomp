#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

extern u8 D_800EA000[];

/* Chooses an available neighboring direction, checking perpendicular alternatives when needed. */
s32 func_8001CBD4(s32 x, s32 y, s32 requested_dir)
{
    register s32 neighbor_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 tile_or_turn ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 direction;
    s32 lookup_value;
    s32 lookup_value_2;
    u32 config_or_dir;
    u32 dir_or_tiles;
    s32 y_offsets;
    u32 x_offsets;
    s16 origin_y;
    s32 origin_x;
    register s32 row_work ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 tiles_or_shift;

    neighbor_x = x;
    tile_or_turn = y;
    direction = requested_dir;
    origin_x = neighbor_x;
    origin_y = tile_or_turn;
    config_or_dir = (u32)&gameWork;
    lookup_value = direction << 16;
    dir_or_tiles = lookup_value >> 16;
    x_offsets = (u32)((s8 *)dirStepX);
    row_work = (s32)dir_or_tiles * 2;
    tiles_or_shift = row_work + x_offsets;
    y_offsets = (u32)((s8 *)dirStepY);
    row_work += y_offsets;
    lookup_value = *(u16 *)tiles_or_shift;
    row_work = *(u16 *)row_work;
    neighbor_x += lookup_value;
    tile_or_turn += row_work;
    tiles_or_shift = (u32)D_800EA000;
    tile_or_turn = (s16)tile_or_turn;
    neighbor_x <<= 16;
    row_work = ((GameWork *)config_or_dir)->unk_1F0;
    neighbor_x >>= 16;
    tile_or_turn = (tile_or_turn << row_work) + neighbor_x;
    if (*(u16 *)(tiles_or_shift + tile_or_turn * 6 + 4) != 0) {
        tile_or_turn = 2;
        config_or_dir = dir_or_tiles;
        dir_or_tiles = tiles_or_shift;
        tiles_or_shift = row_work;
        do {
            lookup_value_2 = ((s32)config_or_dir + tile_or_turn) & 6;
            lookup_value_2 *= 2;
            neighbor_x = *(u16 *)(lookup_value_2 + x_offsets);
            row_work = *(u16 *)(lookup_value_2 + y_offsets);
            neighbor_x = origin_x + neighbor_x;
            row_work = (s16)(origin_y + row_work);
            row_work <<= tiles_or_shift;
            neighbor_x = (s16)neighbor_x;
            row_work += neighbor_x;
            if (*(u16 *)(dir_or_tiles + row_work * 6 + 4) == 0) {
                return (direction + tile_or_turn) & 6;
            }
            tile_or_turn += 4;
        } while (tile_or_turn < 7);
    }
    return (s16)direction;
}
