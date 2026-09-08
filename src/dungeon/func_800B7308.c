#include "common.h"

typedef struct S_8003E2D8 {
    u8 pad_000[0x1DC];
    u8 *table;
    u8 pad_1E0[0x10];
    s16 shift;
} S_8003E2D8;

extern S_8003E2D8 D_80083160;

// Return the negated value of an occupied grid entry at the coordinates, or 0x400.
s16 func_800BCA68(s32 xCoord, s32 yCoord) {
    S_8003E2D8 *gridState = &D_80083160;
    u32 cellIndex;
    u8 *cellEntry;

    cellIndex = (((u32) (yCoord & 0xFFFF) >> 6) << gridState->shift) & 0xFFFF;
    cellIndex += (u32) (xCoord & 0xFFFF) >> 6;
    cellEntry = (u8 *) ((u32) (cellIndex * 6) + (u32) gridState->table);
    if (*(u16 *) cellEntry != 0) {
        return (s16) (0 - *(u16 *) (cellEntry + 2));
    }
    return 0x400;
}
