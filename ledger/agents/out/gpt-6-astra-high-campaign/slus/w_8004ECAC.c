#include "common.h"

typedef struct {
    u8 pad0[0x1E];
    u16 flags; /* offset 0x1E */
} S_8004ECAC;

extern void func_8004EE90(u16 *a0);

/* If flag 0x2000 is set, transfer it to the linked entity and mark this entity and global state dirty. */
void func_8004ECAC(void *link_field)
{
    S_8004ECAC *self = (S_8004ECAC *)((u8 *)link_field - 0x20);
    u16 **linked_entity = (u16 **)link_field;

    if (self->flags & 0x2000) {
        self->flags &= 0xDFFF;
        (*linked_entity)[0xF] |= 0x2000;
        func_8004EE90((u16 *)self);
    }
}
