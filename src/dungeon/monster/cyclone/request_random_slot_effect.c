#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/monster/cyclone.h"




/*
 * For a non-player actor, rolls against its byte at +3 to request status 0x19; returns 1 only if
 * the request succeeds.
 */
s32 request_random_slot_effect(ActorRecord *actor) {
    s32 seed;
    register s32 divisor;
    s32 remainder;
    s16 slot;

    if (actor == dungeon_actor_ring_anchor) {
        return 0;
    }
    seed = generate_random_value() & 0xFFFF;
    if (((s32)(actor->luck)) != 0) {
        divisor = ((s32)(actor->luck));
        remainder = seed % divisor;
        slot = remainder;
    } else {
        slot = 0;
    }
    if (slot < 16) {
        if ((s16)set_or_clear_actor_status_slot(actor, STATUS_ANOREXIA,
                (s8)((actor->level >> 2) + 0x20 + (generate_random_value() & 3))) >= 0) {
            return 1;
        }
    }
    return 0;
}
