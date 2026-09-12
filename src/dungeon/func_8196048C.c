#include "common.h"

typedef struct {
    u16 *tiles;
    u8 pad04[0x10];
    s16 row_shift;
} DungeonMap;

extern u16 D_800273CC[8];
extern u8 D_8002744C[9];
extern u8 D_8002744D[9];
extern u8 D_80083160[0x200];

/* Copies a 7-by-7 tile region from the source grid into the dungeon map around the current coordinates. */
void func_8196048C(void)
{
    s8 *dungeon_state;
    DungeonMap *map;
    s16 row;
    s16 first_column;
    s32 rows_copied;
    s32 columns_copied;
    u16 *source_row;
    u16 *source_tile;
    u16 tile_value;
    u8 center_row;
    u8 center_column;

    dungeon_state = D_80083160;
    map = (DungeonMap *)(dungeon_state + 0x1DC);
    rows_copied = 0;
    source_row = D_800273CC;
    center_row = D_8002744D[0];
    center_column = D_8002744C[0];
    row = center_row - 3;
    first_column = center_column - 3;
    do {
        s16 column;
        s32 row_index;

        column = first_column;
        columns_copied = 0;
        row_index = row;
        source_tile = source_row;
        do {
            tile_value = *source_tile++;
            columns_copied++;
            map->tiles[(column + (row_index << map->row_shift)) * 3 + 1] = tile_value;
            column++;
            if (columns_copied >= 7) {
                break;
            }
        } while (1);
        source_row += 8;
        rows_copied++;
        row++;
    } while (rows_copied < 7);
}

