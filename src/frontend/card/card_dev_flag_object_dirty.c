#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"

/* Set bit 0x8000 in the object and global flags when the object exists. */
void card_dev_flag_object_dirty(ObjectNodeHeader *node) {
    if (node != 0) {
        u16 object_flags = node->flags;
        s32 global_flags = card_ui_dirty_flags;
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        node->flags = object_flags;
        card_ui_dirty_flags = global_flags;
    }
}
