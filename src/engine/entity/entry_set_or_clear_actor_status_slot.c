#include "common.h"
#include "shared/game_state.h"
#include "dungeon/actor/status.h"
#include "shared/actor_status.h"
#include "shared/entity.h"


#include "shared/sys_flags.h"
#include "engine/entity.h"
#include "engine/util.h"


/* Remove type 0x1B and replay the remaining slots with global flag bit 1 set. */
void replay_actor_status_slots(ActorRecord *object)
{
    ActorStatusSlot saved_slots[4];
    s32 initial_type = 0x1B;
    s32 slot_index;
    u16 saved_flags;

    saved_flags = GAME_STATE->log.head.flags;
    GAME_STATE->log.head.flags = saved_flags | 2;
    take_status_slot_value(object, initial_type);
    slot_index = 0;

    for (; slot_index < 4; slot_index++) {
        saved_slots[slot_index] = object->status[slot_index];
        if (saved_slots[slot_index].type != 0) {
            take_status_slot_value(object, saved_slots[slot_index].type);
        }
    }

    for (slot_index = 0; slot_index < 4; slot_index++) {
        if (saved_slots[slot_index].type != 0) {
            set_or_clear_actor_status_slot(object, saved_slots[slot_index].type, saved_slots[slot_index].value);
        }
    }

    system_update_flags = saved_flags;
}
