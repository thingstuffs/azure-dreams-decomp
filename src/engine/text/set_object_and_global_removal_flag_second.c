#include "common.h"
#include "engine/text.h"

typedef struct {
    u8 pad0[0x1E];
    u16 flags; /* offset 0x1E */
} S_8004ECAC;

/* If flag 0x2000 is set, transfer it to the linked entity and mark this entity and global state dirty. */
void propagate_linked_removal_request(void *link_field)
{
    S_8004ECAC *self = (S_8004ECAC *)((u8 *)link_field - 0x20);
    u16 **linked_entity = (u16 **)link_field;

    if (self->flags & 0x2000) {
        self->flags &= 0xDFFF;
        (*linked_entity)[0xF] |= 0x2000;
        set_object_and_global_removal_flag((u16 *)self);
    }
}
