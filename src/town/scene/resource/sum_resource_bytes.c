#include "common.h"

extern s32 resource_cache_records[];

/* Sum the second word of each requested table entry. */
s32 sum_resource_bytes(s32 entry_count) {
    s32 *entry;
    s32 sum;
    s32 i;

    sum = 0;
    for (i = 0; i < entry_count; i++) {
        entry = &resource_cache_records[i * 2];
        sum += entry[1];
    }
    return sum;
}
