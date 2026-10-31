#include "common.h"
#include "shared/object_node.h"
#include "engine/text.h"

/* If flag 0x2000 is set, transfer it to the linked entity and mark this entity and global state dirty. */
void propagate_linked_removal_request(void *link_field)
{
    ObjectNodeHeader *self = (ObjectNodeHeader *)((u8 *)link_field - 0x20);
    u16 **linked_entity = link_field;

    if (self->flags & 0x2000) {
        self->flags &= 0xDFFF;
        (*linked_entity)[0xF] |= 0x2000;
        set_object_and_global_removal_flag((u16 *)self);
    }
}
