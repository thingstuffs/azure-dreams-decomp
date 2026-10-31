#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "dungeon/actor.h"

/* Tests the flag on this entity, or on either linked entity for aggregate records. */
s32 is_linked_entity_flagged_80000(ActorRecord *entity, ActorRecord *unused_context)
{
    if (entity->flags14 & ACTOR_PARTY_MEMBER) {
        s32 index;
        for (index = 1; index >= 0; index--) {
            EntityRec *linked = ((EntityRec **)&dungeon_actor_ring_anchor->unk_AC.address)[index];
            if (linked != 0 && (linked->unk_54 & 0x80000)) {
                return 1;
            }
        }
    } else if (entity->status_flags & 0x80000) {
        return 1;
    }
    return 0;
}
