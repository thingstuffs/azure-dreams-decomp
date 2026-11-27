#include "common.h"
#include "town/scene/resource.h"

typedef struct TownEntry {
    s8 flag_bit;
    s8 high_key;
    s16 low_key;
    s32 field4;
} TownEntry;

extern TownEntry resource_cache_records[];

// Finds a town entry by its three key fields, returning the end index with its high bit set if absent.
s32 find_resource_index_by_key(s32 targetField0, s32 targetField1, s32 targetField2) {
    s32 entryIndex;

    for (entryIndex = 0; resource_cache_records[entryIndex].high_key != -1; entryIndex++) {
        if (targetField0 == resource_cache_records[entryIndex].flag_bit &&
            targetField1 == resource_cache_records[entryIndex].high_key &&
            targetField2 == resource_cache_records[entryIndex].low_key) {
            return entryIndex;
        }
    }
    return entryIndex - 0x80000000;
}
