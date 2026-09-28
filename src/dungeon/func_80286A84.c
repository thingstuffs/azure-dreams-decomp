#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u16 active;
    s16 value;
    s16 unused;
} DungeonCell;

extern DungeonCell D_800EA000[];

// Sets the value of inactive dungeon cells in rows and columns 1 through 62.
void func_80019A84(s16 value) {
    MapGrid *state;
    DungeonCell *cells;
    s32 row;
    s32 column;

    state = &gameWork.map;
    cells = D_800EA000;
    row = 1;
    do {
        column = 1;
        do {
            DungeonCell *cell;
            unsigned long cellAddress;

            cellAddress = (column + (row << state->shiftX)) * 6;
            cellAddress += (unsigned long)cells;
            cell = (DungeonCell *)cellAddress;
            if (cell->active == 0) {
                cell->value = value;
            }
            column++;
        } while (column < 0x3F);
        row++;
    } while (row < 0x3F);
}
