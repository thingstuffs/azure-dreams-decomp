#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E99C();                         /* extern */

/* Pass the first value of each pointed-to entry, starting at slot 20, to func_8004E99C. */
void func_800AF0E0(s32 entryTableAddress, s32 entryCount) {
    s32 **entryCursor;
    s32 *entry;
    s32 endIndex;
    s32 entryIndex;

    entryIndex = 0x14;
    entryCount += 0x14;
    if (entryIndex < entryCount) {
        endIndex = entryCount;
        entryCursor = entryTableAddress + 0x50;
        do {
            entry = *entryCursor;
            entryCursor += 1;
            entryIndex += 1;
            func_8004E99C(*entry);
        } while (entryIndex < endIndex);
    }
}
