#include "common.h"

#include "common.h"
#include "engine/resource.h"
#include "slus/data.h"

/* Returns the table value for the lookup key, or zero if no entry is found. */
s32 lookup_sentinel_resource_value_or_zero(s32 lookup_key) {
    s32 index = runtime_find_sentinel_table_value(lookup_key);

    if (index < 0) {
        return 0;
    }

    return resource_sentinel_values[index];
}
