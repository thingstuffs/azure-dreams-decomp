#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/record_ptrs.h"

typedef struct Actor {
    u8 pad0[0x14];
    s32 flags14;
    u8 pad1[0x3C];
    s32 flags54;
} Actor;

typedef struct Slot {
    u8 pad0[0xAC];
    Actor *other;
} Slot;


/* Tests the global override or flag 0x20000 on the actor or its linked actors. */
s32 check_global_or_linked_flag_20000(Actor *actor) {
    if (dungeon_floor_flags & 0x10000000) {
        return 1;
    }
    if (actor->flags14 & ACTOR_PARTY_MEMBER) {
        s32 slot_index = 1;
        u8 *slot_cursor = ((u8 *)dungeon_actor_ring_anchor) + 4;
        do {
            Actor *linked_actor = ((Slot *)slot_cursor)->other;
            if ((linked_actor != 0) && (linked_actor->flags54 & 0x20000)) {
                return 1;
            }
            slot_index--;
            slot_cursor -= 4;
        } while (slot_index >= 0);
    } else if (actor->flags54 & 0x20000) {
        return 1;
    }
    return 0;
}
