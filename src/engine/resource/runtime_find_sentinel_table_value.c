#include "common.h"

#include "common.h"
#include "engine/resource.h"
#include "slus/data.h"

/* Returns the index of a value in the sentinel-terminated table, or -1 if absent. */
u32 runtime_find_sentinel_table_value(s32 value)
{
    s32 index;

    for (index = 0; resource_sentinel_keys[index] != -1; index++) {
        if (resource_sentinel_keys[index] == value) {
            return index;
        }
    }

    return -1;
}
