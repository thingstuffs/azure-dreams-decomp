#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "dungeon/actor/object.h"

/* Returns 1 when the entity carries the derived blindness-protection bit 0x08000000 at +0x54 (the bit that installs
 * ACTOR_RESIST_BLIND), or, for a party member, when either linked entity does. */
s32 has_blindness_protection(EntityRec *entity)
{
    if (entity->flags14 & ACTOR_PARTY_MEMBER) {
        s32 index;
        for (index = 1; index >= 0; index--) {
            EntityRec *linked = ((EntityRec **)&dungeon_actor_ring_anchor->unk_AC.address)[index];
            if (linked != 0 && (linked->unk_54 & 0x8000000)) {
                return 1;
            }
        }
    } else if (entity->unk_54 & 0x8000000) {
        return 1;
    }
    return 0;
}
