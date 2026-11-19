#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "dungeon/actor.h"

/* Tests the flag on this entity, or on either linked entity for aggregate records. */
s32 has_brainwash_protection(ActorRecord *entity)
{
    if (entity->flags14 & ACTOR_PARTY_MEMBER) {
        s32 index;
        for (index = 1; index >= 0; index--) {
            ActorRecord *linked = ((ActorRecord **)&dungeon_actor_ring_anchor->unk_AC.address)[index];
            if (linked != 0 && (linked->status_flags & 0x100000)) {
                return 1;
            }
        }
    } else if (entity->status_flags & 0x100000) {
        return 1;
    }
    return 0;
}
