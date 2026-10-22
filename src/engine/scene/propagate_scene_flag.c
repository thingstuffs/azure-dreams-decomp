#include "common.h"
#include "shared/object_flags.h"
#include "engine/graphics.h"

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

/* Propagates the second entity's 0x2000 flag and marks the record and global flags after scene_load_variant_texture_set. */
void propagate_scene_flag(S_800510DC *record)
{
    S_800510DC_Ent *entity;

    if (record->field4->flags & 0x2000) {
        scene_load_variant_texture_set();
        entity = record->field0;
        entity->flags |= 0x2000;
        *(u16 *)((u8 *)record - 2) |= NODE_REMOVE;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
