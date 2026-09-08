#include "common.h"

#include "common.h"

// Sets bit 15 on 255 consecutive entries or the last 15 entries of each 16-entry group.
void func_80047200(u16 *entry, s32 groupCount, s32 contiguousMode)
{
    register s32 groupIndex;
    register s32 entryIndex;

    entryIndex = 1;
    if (contiguousMode == 0) {
        groupIndex = 0;
        if (groupCount > 0) {
            do {
                entry++;
                for (entryIndex = 1; entryIndex < 0x10; entryIndex++) {
                    *entry |= 0x8000;
                    entry++;
                }
                groupIndex++;
            } while (groupIndex < groupCount);
        }
    } else {
        for (; entryIndex < 0x100; entryIndex++) {
            *entry |= 0x8000;
            entry++;
        }
    }
}
