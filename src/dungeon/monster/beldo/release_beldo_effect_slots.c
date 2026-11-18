
struct ObjectNodeHeader;
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_node.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/monster/beldo/command_ticks_data.h"
#include "dungeon/level.h"

extern void func_80173A48(void);

/* Clear the state flag, run the shared update, and process both occupied object slots. */
void release_beldo_effect_slots(void)
{
    s16 slot;
    void *object;
    ActorRecord *state;

    slot = 0;
    state = NODE_BODY(beldo_active_entity);
    state->action_flags &= 0x7FFF;
    func_80173A48();
    do {
        object = *(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + slot * 4);
        if (object != 0) {
            insert_node_before_primary_actor(NODE_HEADER(object));
        }
        slot++;
    } while (slot < 2);
}
