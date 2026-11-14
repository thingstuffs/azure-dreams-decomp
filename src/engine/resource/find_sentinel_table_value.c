#include "common.h"

#include "engine/resource.h"
#include "slus/data.h"

/* Returns the table value for the lookup key, or zero if no entry is found. */
s32 lookup_resource_value(s32 lookup_key) {
    s32 index = find_resource_key_index(lookup_key);

    if (index < 0) {
        return 0;
    }

    return resource_sentinel_values[index];
}
