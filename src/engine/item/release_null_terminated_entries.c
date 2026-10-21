#include "common.h"
#include "engine/item.h"
#include "engine/resource.h"

/* Flags each entry in a null-terminated pointer array. */
void release_null_terminated_entries(u16 **entries)
{
    while (*entries != 0) {
        flag_object_for_removal(*entries);
        entries++;
    }
}
