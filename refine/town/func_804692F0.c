#include "common.h"

extern u8 D_8001791C[96];
s32 func_8001E670();

// Count entries 1 through 7 whose field at offset 4 passes func_8001E670.
s32 func_8001A2F0(void) {
    s32 matchingEntryCount;
    s32 entryIndex;
    u8 *entry;
    u8 *entryTable;

    matchingEntryCount = 0;
    entryIndex = 1;
    entryTable = D_8001791C;
    entry = entryTable + 0xC;
    do {
        if (func_8001E670(*(s16 *)(entry + 4)) != 0) {
            matchingEntryCount += 1;
        }
        entryIndex += 1;
        entry += 0xC;
    } while (entryIndex < 8);
    return matchingEntryCount;
}
