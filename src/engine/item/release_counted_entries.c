#include "common.h"
#include "engine/item.h"
#include "engine/resource.h"

/* Flags each non-null entry in the counted array and clears its pointer. */
void release_counted_entries(u16 **entries, s32 count)
{
    s32 index;

    for (index = 0; index < count; index++) {
        if (entries[index] != 0) {
            func_8004B1A4(entries[index]);
            entries[index] = 0;
        }
    }
}
