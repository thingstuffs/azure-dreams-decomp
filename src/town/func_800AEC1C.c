#include "common.h"
#include "shared/game_work.h"

extern s16 D_80080B04;
extern u8 *D_80081508;

// Clear bit 0x4000 in each listed grid cell, then reset the list and its state.
void func_800AC37C(void) {
    u8 *coordinateEntry;
    u16 *cell;
    u16 cellFlags;
    MapGrid *gridDescriptor;
    u8 *gridBase;

    gridDescriptor = &gameWork.map;
    coordinateEntry = D_80081508;
    gridBase = ((u8 *)gridDescriptor->cells);
    if (*coordinateEntry != 0) {
        do {
            cell = (u16 *)(gridBase +
                (coordinateEntry[0] + (coordinateEntry[1] << gridDescriptor->shiftX)) * 2);
            cellFlags = *cell;
            coordinateEntry += 4;
            *cell = cellFlags & 0xBFFF;
        } while (*coordinateEntry != 0);
    }
    D_80080B04 = 0;
    *D_80081508 = 0;
}
