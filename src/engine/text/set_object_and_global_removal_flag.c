#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "engine/text.h"

/* Sets bit 0x8000 in the object and global flags when the object exists. */
void set_object_and_global_removal_flag(struct ObjectNodeHeader *node)
{
    if (node != 0) {
        u16 flags = node->flags;
        int global_flags = object_flag_block.flags;
        node->flags = flags | NODE_REMOVE;
        object_flag_block.flags = global_flags | OBJECT_REMOVE_PENDING;
    }
}
