#include "town/scene/resource/resource_install_g00520.h"
#include "town/scene/resource.h"

/* Clear one cache entry and mark its key as the end of the resource list. */
void reset_resource_entry(s32 index) {
    TownAllocEntry *entry;

    entry = &resource_cache_records[index];
    entry->kind = 0;
    entry->state = -1;
    entry->value = 0;
    entry->size = 0;
}
