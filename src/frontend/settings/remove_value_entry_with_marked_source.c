#include "shared/object_node.h"
#include "common.h"
#include "shared/object_links.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "frontend/settings.h"

/* Propagates the linked record high flag to the record and global flags. */
void remove_value_entry_with_marked_source(MainTitleValueEntry *entry) {
    if ((s16)entry->owner->flags & NODE_REMOVE) {
        NODE_HEADER(entry)->flags |= NODE_REMOVE;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
