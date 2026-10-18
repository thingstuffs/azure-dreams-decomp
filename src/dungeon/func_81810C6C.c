#include "modules/dungeon_ovl_1830850.h"

void *inventory_initialize_five_shared_entries(void *entryBuffer) {
    s32 entryIndex;
    s32 sharedEntryValue;
    ovl_1830850_81810C6C_Entry *entries;

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
    ((ovl_1830850_81810C6C_Entry *)((entryIndex * 12) + entryBuffer))[-1].f0 = 128;
    return entryBuffer;
}
