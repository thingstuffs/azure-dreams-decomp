#include "shared/object_node.h"
#include "common.h"
#include "shared/object_links.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "frontend/settings.h"

/* Propagates the linked record high flag to the record and global flags. */
void propagate_record_high_bit(void *record_arg) {
    ObjectNodeHeader *record = record_arg;
    MainTitleValueEntry *entry = record_arg;

    if (*(s16 *)((u8 *)entry->value_data + 0x16) & 0x8000) {
        (record - 1)->flags = (u16) ((record - 1)->flags
            | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
