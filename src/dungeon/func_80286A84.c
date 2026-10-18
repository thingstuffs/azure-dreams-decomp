#include "modules/dungeon_floor_generate.h"

void fill_inactive_interior_cells(s16 value) {
    MapGrid *state;
    floor_generate_isolated_80286A84_DungeonCell *cells;
    s32 row;
    s32 column;

    state = &g_game_work.map;
    cells = ((floor_generate_isolated_80286A84_DungeonCell *)D_800EA000);
    row = 1;
    do {
        column = 1;
        do {
            floor_generate_isolated_80286A84_DungeonCell *cell;
            unsigned long cellAddress;

            cellAddress = (column + (row << state->shiftX)) * 6;
            cellAddress += (unsigned long)cells;
            cell = (floor_generate_isolated_80286A84_DungeonCell *)cellAddress;
            if (cell->active == 0) {
                cell->value = value;
            }
            column++;
        } while (column < 0x3F);
        row++;
    } while (row < 0x3F);
}
