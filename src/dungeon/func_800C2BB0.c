#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"

/* Tests the flag on this entity, or on either linked entity for aggregate records. */
s32 func_800C8310(EntityRec *entity, void *unused_context)
{
    if (entity->flags14 & 0x4000) {
        s32 index;
        for (index = 1; index >= 0; index--) {
            EntityRec *linked = ((EntityRec **)&D_800E3D7C->unk_AC)[index];
            if (linked != 0 && (linked->unk_54 & 0x80000)) {
                return 1;
            }
        }
    } else if (entity->unk_54 & 0x80000) {
        return 1;
    }
    return 0;
}
