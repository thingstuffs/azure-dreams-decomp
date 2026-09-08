#include "common.h"

typedef struct {
    u8 pad[0x14];
    s16 shift;
    u8 tail[10];
} DungeonInfo;

extern u8 D_800E9FFA[];

/* Writes the corners and edges of a rectangular border in the dungeon tile grid. */
void func_8001D9CC(s16 left_x, s16 top_y, s16 right_x, s16 bottom_y, s32 tile_value_base) {
    s16 *tile;
    s16 *opposite_tile;
    register u8 *info_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register DungeonInfo *info ASM_REG("$25");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 tile_value ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 bottom_row;
    s16 x;
    s16 y;
    s16 right_col;
    info_page = (u8 *)0x80080000;
    ASM_KEEP_NV(info_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    info = (DungeonInfo *)(info_page + 0x333c);
    bottom_row = bottom_y;
    tile = (s16 *)(D_800E9FFA + (((((s16)top_y - 1) << info->shift) + left_x) * 6));
    tile[0] = 0xE;
    tile_value = tile_value_base + 0x40;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(D_800E9FFA + 6 + (((((s16)top_y - 1) << info->shift) + right_x) * 6));
    tile[0] = 0xB;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(D_800E9FFA + ((((bottom_row << info->shift) + left_x) * 6)));
    tile[0] = 0xD;
    tile[1] = tile_value;
    tile[2] = 9;

    right_col = right_x;
    tile = (s16 *)(D_800E9FFA + 6 + ((((bottom_row << info->shift) + right_x) * 6)));
    tile[0] = 0xC;
    tile[1] = tile_value;
    tile[2] = 9;

    tile = (s16 *)(D_800E9FFA + 6 + (((((s16)top_y - 1) << info->shift) + left_x) * 6));
    opposite_tile = (s16 *)(D_800E9FFA + 6 + (((bottom_row << info->shift) + left_x) * 6));
    x = left_x;
    if (left_x < right_x) {
        do {
            x++;
            tile[0] = 0x12;
            opposite_tile[0] = 0x10;
            opposite_tile[1] = tile_value;
            tile[1] = tile_value;
            opposite_tile[2] = 9;
            tile[2] = 9;
            tile += 3;
            opposite_tile += 3;
        } while (x < right_x);
    }

    y = top_y;
    tile = (s16 *)(D_800E9FFA + ((((y << info->shift) + left_x) * 6)));
    opposite_tile = (s16 *)(D_800E9FFA + 6 + ((((y << info->shift) + right_col) * 6)));
    ASM_USE_NV(bottom_row);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (y < bottom_row) {
        do {
            y++;
            tile[0] = 0x11;
            opposite_tile[0] = 0xF;
            opposite_tile[1] = tile_value;
            tile[1] = tile_value;
            opposite_tile[2] = 9;
            tile[2] = 9;
            tile = (s16 *)((u8 *)tile + (6 << info->shift));
            opposite_tile = (s16 *)((u8 *)opposite_tile + (6 << info->shift));
        } while (y < bottom_row);
    }
}
