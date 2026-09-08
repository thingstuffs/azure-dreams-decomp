#include "common.h"

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083350[5];
extern u8 D_800EA000[];

/* Chooses an available neighboring direction, checking perpendicular alternatives when needed. */
s32 func_8001CBD4(s32 x, s32 y, s32 requested_dir)
{
    register s32 neighbor_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 tile_or_turn ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 direction;
    register s32 lookup_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u32 config_or_dir;
    register u32 dir_or_tiles ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 y_offsets;
    u32 x_offsets;
    register s32 origin_y ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 origin_x;
    register s32 row_work ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 tiles_or_shift;

    neighbor_x = x;
    tile_or_turn = y;
    direction = requested_dir;
    origin_x = neighbor_x;
    ASM_KEEP_NV(origin_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    origin_y = tile_or_turn;
    ASM_KEEP_NV(origin_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    config_or_dir = 0x80080000;
    ASM_KEEP_NV(config_or_dir);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    lookup_value = direction << 16;
    dir_or_tiles = lookup_value >> 16;
#ifdef NON_MATCHING
    x_offsets = (u32)&D_8006CCD8;
#else
    lookup_value = 0x80070000;
    ASM_KEEP_NV(lookup_value);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    x_offsets = lookup_value - 0x3328;
#endif
    ASM_KEEP_NV(x_offsets);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    row_work = (s32)dir_or_tiles * 2;
    tiles_or_shift = row_work + x_offsets;
#ifdef NON_MATCHING
    y_offsets = (u32)&D_8006CCE8;
#else
    lookup_value = 0x80070000;
    ASM_KEEP_NV(lookup_value);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    y_offsets = lookup_value - 0x3318;
#endif
    ASM_KEEP_NV(y_offsets);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    row_work += y_offsets;
    lookup_value = *(u16 *)tiles_or_shift;
    row_work = *(u16 *)row_work;
    neighbor_x += lookup_value;
    tile_or_turn += row_work;
#ifdef NON_MATCHING
    tiles_or_shift = (u32)D_800EA000;
#else
    lookup_value = 0x800F0000;
    ASM_KEEP_NV(lookup_value);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    tiles_or_shift = lookup_value - 0x6000;
#endif
    tile_or_turn = (s16)tile_or_turn;
    neighbor_x <<= 16;
    row_work = *(s16 *)(config_or_dir + 0x3350);
    neighbor_x >>= 16;
    tile_or_turn = (tile_or_turn << row_work) + neighbor_x;
    if (*(u16 *)(tiles_or_shift + tile_or_turn * 6 + 4) != 0) {
        tile_or_turn = 2;
        config_or_dir = dir_or_tiles;
        dir_or_tiles = tiles_or_shift;
        tiles_or_shift = row_work;
        do {
            lookup_value = ((s32)config_or_dir + tile_or_turn) & 6;
            lookup_value *= 2;
            neighbor_x = *(u16 *)(lookup_value + x_offsets);
            row_work = *(u16 *)(lookup_value + y_offsets);
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
