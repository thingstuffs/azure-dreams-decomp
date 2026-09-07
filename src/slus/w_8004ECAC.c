#include "common.h"

/* If self->flags (entity offset 0x1E) has bit 0x2000 set: clear it on self,
 * set the same bit 0x2000 on the flags word of the entity pointed to by the
 * pointer stored at arg0 (entity offset 0x20), then call func_8004EE90(self)
 * to mark self "used" (bit 0x8000) and set the global dirty flag. */
/* Sub-object pointer convention shared with func_80048D60/func_8004EE90 etc:
 * arg0 == entity_base + 0x20. self->flags lives at entity offset 0x1E
 * (== arg0 - 0x20 + 0x1E). The pointer stored AT arg0 (entity offset 0x20)
 * points at another entity whose flags is likewise at +0x1E (index 0xF as
 * u16*, matching func_8004EE90's own indexing convention). */
typedef struct {
    u8 pad0[0x1E];
    u16 flags; /* offset 0x1E */
} S_8004ECAC;

extern void func_8004EE90(u16 *a0);

void func_8004ECAC(void *arg0)
{
    S_8004ECAC *self = (S_8004ECAC *)((u8 *)arg0 - 0x20);
    u16 **linkp = (u16 **)arg0; /* field at arg0 + 0x0 */

    if (self->flags & 0x2000) {
        self->flags &= 0xDFFF;
        (*linkp)[0xF] |= 0x2000;
        func_8004EE90((u16 *)self);
    }
}
