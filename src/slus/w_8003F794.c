#include "common.h"
#include "shared/transition_slots.h"

/* Initializes the last free slot and returns its index, or -1 if all eight slots are occupied. */
s16 func_8003F794(s16 slot_id, s16 slot_value)
{
    s32 slot_index;
    u32 last_slot_index;
    TransitionSlot *slot;

    slot_index = 7;
    last_slot_index = 7;
    slot = &D_80083120[last_slot_index];
    do {
        if (slot->type == 0)
            goto found;
        slot_index--;
        slot--;
    } while (slot_index >= 0);
    return -1;
found:
    slot->type = slot_id;
    slot->unk_2 = 0;
    slot->param = slot_value;
    slot->unk_6 = 0;
    return slot_index;
}
