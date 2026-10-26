#include "common.h"
#include "shared/game_work.h"


// Return the negated value of an occupied grid entry at the coordinates, or 0x400.
s16 get_surface_height_at_coordinates(s32 xCoord, s32 yCoord) {
    GameWork *gridState = &g_game_work;
    u32 cellIndex;
    u8 *cellEntry;

    cellIndex = (((u32) (yCoord & 0xFFFF) >> 6) << gridState->map.shiftX) & 0xFFFF;
    cellIndex += (u32) (xCoord & 0xFFFF) >> 6;
    cellEntry = (u8 *) ((u32) (cellIndex * 6) + (unsigned long)((u8 *)gridState->map.cells));
    if (*(u16 *) cellEntry != 0) {
        return (s16) (0 - *(u16 *) (cellEntry + 2));
    }
    return 0x400;
}
