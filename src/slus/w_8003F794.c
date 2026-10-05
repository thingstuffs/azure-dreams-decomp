#include "common.h"
#include "shared/transition_slots.h"

/* Initializes the last free slot and returns its index, or -1 if all eight slots are occupied. */
s16 func_8003F794(s16 slot_id, s16 slot_value)
{
    s32 slot_index;
    TransitionSlot *slot;

    for (slot_index = 7; slot_index >= 0; slot_index--) {
        slot = &D_80083120[slot_index];
        if (slot->type == 0) {
            slot->type = slot_id;
            slot->unk_2 = 0;
            slot->param = slot_value;
            slot->unk_6 = 0;
            return slot_index;
        }
    }
    return -1;
}
