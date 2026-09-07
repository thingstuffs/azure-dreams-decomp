#include "common.h"

extern s32 func_800188E4();
extern s16 D_80019088[28];

// Passes seven strided table values and three fixed values to func_800188E4.
void func_800168E0(void) {
    s16 *tableEntry;
    s32 entryCount;

    entryCount = 0;
    tableEntry = D_80019088;
    do {
        s32 entryValue = *tableEntry;

        tableEntry += 4;
        entryCount += 1;
        func_800188E4(entryValue);
    } while (entryCount < 7);

    func_800188E4(0x60E);
    func_800188E4(0x606);
    func_800188E4(0x611);
}
