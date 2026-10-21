#include "common.h"

#include "common.h"
#include "engine/resource.h"

/* Checks whether the indexed table entry has a nonzero first word. */
s32 has_table_entry(s32 unused, s32 entry_index) {
    s32 entry_table;

    if ((entry_index < 0) || (entry_table = lookup_sentinel_resource_value_or_zero(unused), (entry_table == 0))) {
        return 0;
    }
    return (*(s32 *)((u8 *)(entry_table) + ((entry_index) * 8))) != 0;
}
