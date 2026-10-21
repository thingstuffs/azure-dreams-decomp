#include "common.h"

#include "common.h"
#include "engine/message.h"

typedef struct {
    s8 type;
    s8 value;
} Slot;

typedef struct {
    u8 pad[0x2C];
    Slot slots[4];
} SlotOwner;

/* Clear slots of the requested type and notify the owner after each match. */
void clear_slots_of_type(SlotOwner *owner, s8 match_type)
{
    s32 slot_index;
    s8 slot_type;

    for (slot_index = 3; slot_index >= 0; slot_index--) {
        slot_type = owner->slots[slot_index].type;
        if (slot_type == match_type) {
            owner->slots[slot_index].type = 0;
            owner->slots[slot_index].value = 0;
            end_status_effect_message(owner, match_type);
        }
    }
}
