#include "common.h"

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    s8 f3;
    s32 f4;
    u8 pad[2];
    u8 f10;
    u8 f11;
} Entry;

extern s32 D_800294E4;

/* Initializes five entries with shared defaults and marks the final entry. */
void *func_80025C6C(void *entryBuffer) {
    s32 entryIndex;
    s32 sharedEntryValue;
    Entry *entries;

    entryIndex = 0;
    entries = entryBuffer;
    do {
        entries[entryIndex].f1 = 40;
        sharedEntryValue = D_800294E4;
        entries[entryIndex].f3 = (entryIndex * 16) - 62;
        entries[entryIndex].f2 = 2;
        entries[entryIndex].f10 = 12;
        entries[entryIndex].f11 = 12;
        entries[entryIndex].f4 = sharedEntryValue;
        entryIndex += 1;
    } while (entryIndex < 5);
    ((Entry *)((entryIndex * 12) + entryBuffer))[-1].f0 = 128;
    return entryBuffer;
}
