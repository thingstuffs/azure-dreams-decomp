#include "common.h"

/* generic sub-entity type: only offset 0x1E (a "used"/flags halfword) is
 * accessed by this function. */
typedef struct {
    u8 pad[0x1E];
    u16 flags; /* offset 0x1E */
} S_800510DC_Ent;

/* record points 2 bytes into a larger record: offset -2 holds a u16 flags word
 * belonging to the record itself; offset 0/4 hold pointers to sub-entities
 * of type S_800510DC_Ent. */
typedef struct {
    S_800510DC_Ent *field0; /* offset 0x0 */
    S_800510DC_Ent *field4; /* offset 0x4 */
} S_800510DC;

extern int D_800814A0; /* global 32-bit "used"/flags word */
extern void func_80051228(void);

/* Propagates the second entity's 0x2000 flag and marks the record and global flags after func_80051228. */
void func_800510DC(S_800510DC *record)
{
    S_800510DC_Ent *entity;

    if (record->field4->flags & 0x2000) {
        func_80051228();
        entity = record->field0;
        entity->flags |= 0x2000;
        *(u16 *)((u8 *)record - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
