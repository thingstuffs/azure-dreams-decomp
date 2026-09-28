#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s8 pad[0x14];
    s16 shift;
} DungeonState;

typedef struct {
    u16 active;
    s16 value;
    s16 unused;
} DungeonCell;

extern DungeonCell D_800EA000[];

// Sets the value of inactive dungeon cells in rows and columns 1 through 62.
void func_80019A84(s16 value) {
    DungeonState *state;
    DungeonCell *cells;
    s32 row;
    s32 column;

    state = ((DungeonState *)((u8 *)&gameWork + 476));
    cells = D_800EA000;
    row = 1;
    do {
        column = 1;
        do {
            DungeonCell *cell;
            unsigned long cellAddress;

            cellAddress = (column + (row << state->shift)) * 6;
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
