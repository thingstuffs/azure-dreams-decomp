#include "common.h"
#include "engine/effect/resource_transition.h"
#include "engine/text.h"

/* If flag 0x2000 is set, transfer it to the linked entity and mark this entity and global state dirty. */
void propagate_linked_removal_request(struct ResourceTransitionBody *body)
{
    ObjectNodeHeader *self = NODE_HEADER(body);

    if (self->flags & 0x2000) {
        self->flags &= 0xDFFF;
        body->owner->flags |= 0x2000;
        set_object_and_global_removal_flag(self);
    }
}
