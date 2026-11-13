#include "common.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "dungeon/item.h"
#include "dungeon/item/state.h"

/* Update proximity state for each actor in the list. */
void update_all_actor_proximity_flags(s16 near_limit, s16 far_limit) {
    ActorRecord *actor;

    actor = NODE_BODY(dungeon_actor_ring_anchor->next_actor_header);
    if (actor != dungeon_actor_ring_anchor) {
        do {
            update_actor_proximity_flag(NODE_HEADER(actor)->sprite, actor, near_limit, far_limit,
                (void *) ((u8 *) actor + 0x9C));
            actor = NODE_BODY(actor->next_actor_header);
        } while (actor != dungeon_actor_ring_anchor);
    }
}
