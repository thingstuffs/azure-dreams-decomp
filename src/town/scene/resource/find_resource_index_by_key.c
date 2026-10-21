#include "common.h"

typedef struct TownEntry {
    s8 field0;
    s8 field1;
    s16 field2;
    s32 field4;
} TownEntry;

extern TownEntry resource_cache_records[];

// Finds a town entry by its three key fields, returning the end index with its high bit set if absent.
s32 find_resource_index_by_key(s32 targetField0, s32 targetField1, s32 targetField2) {
    s32 entryIndex;

    for (entryIndex = 0; resource_cache_records[entryIndex].field1 != -1; entryIndex++) {
        if (targetField0 == resource_cache_records[entryIndex].field0 &&
            targetField1 == resource_cache_records[entryIndex].field1 &&
            targetField2 == resource_cache_records[entryIndex].field2) {
            return entryIndex;
        }
    }
    return entryIndex - 0x80000000;
}
