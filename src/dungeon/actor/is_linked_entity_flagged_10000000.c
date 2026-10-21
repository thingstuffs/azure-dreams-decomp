#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"

/* Tests the flag on this entity, or on either linked entity for aggregate records. */
s32 is_linked_entity_flagged_10000000(EntityRec *entity)
{
    if (entity->flags14 & 0x4000) {
        s32 index;
        for (index = 1; index >= 0; index--) {
            EntityRec *linked = ((EntityRec **)&dungeon_actor_ring_anchor->unk_AC)[index];
            if (linked != 0 && (linked->unk_54 & 0x10000000)) {
                return 1;
            }
        }
    } else if (entity->unk_54 & 0x10000000) {
        return 1;
    }
    return 0;
}
