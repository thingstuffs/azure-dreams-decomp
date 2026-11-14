
struct ObjectNodeHeader;
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_node.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/level.h"

extern void func_80173A48(void);

extern u8 *beldo_active_entity;

/* Clear the state flag, run the shared update, and process both occupied object slots. */
void release_beldo_effect_slots(void)
{
    s16 slot;
    void *object;
    u8 *state;

    slot = 0;
    state = beldo_active_entity + 0x20;
    *(u16 *)(state + 0x46) &= 0x7FFF;
    func_80173A48();
    do {
        object = *(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + slot * 4);
        if (object != 0) {
            clear_entry_flag_and_link_owner(NODE_HEADER(object));
        }
        slot++;
    } while (slot < 2);
}
