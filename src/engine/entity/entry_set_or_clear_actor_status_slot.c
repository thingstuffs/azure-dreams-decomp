#include "common.h"
#include "shared/actor_status.h"
#include "shared/entity.h"


#include "shared/sys_flags.h"
#include "engine/entity.h"
#include "engine/util.h"

extern void set_or_clear_actor_status_slot(ActorRecord *object, s32 type, s32 value);

/* Remove type 0x1B and replay the remaining slots with global flag bit 1 set. */
void replay_actor_status_slots(ActorRecord *object)
{
    ActorStatusSlot saved_slots[4];
    s32 initial_type = 0x1B;
    s32 slot_index;
    u8 *page = (u8 *)0x80010000;
    u16 saved_flags;

    saved_flags = *(u16 *)(page + 0x3714);
    *(u16 *)(page + 0x3714) = saved_flags | 2;
    func_80042518(object, initial_type);
    slot_index = 0;

    for (; slot_index < 4; slot_index++) {
        saved_slots[slot_index] = object->status[slot_index];
        if (saved_slots[slot_index].type != 0) {
            func_80042518(object, saved_slots[slot_index].type);
        }
    }

    for (slot_index = 0; slot_index < 4; slot_index++) {
        if (saved_slots[slot_index].type != 0) {
            set_or_clear_actor_status_slot(object, saved_slots[slot_index].type, saved_slots[slot_index].value);
        }
    }

    system_update_flags = saved_flags;
}
