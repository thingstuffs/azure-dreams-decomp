#include "common.h"

#include "common.h"

typedef struct {
    s8 type;
    s8 value;
} Slot;

typedef struct {
    u8 pad[0x2C];
    Slot slots[4];
} SlotOwner;

extern void func_80042BDC();

/* Clear slots of the requested type and notify the owner after each match. */
void func_80042B68(SlotOwner *owner, s8 match_type)
{
    s32 slot_index;
    s8 slot_type;

    for (slot_index = 3; slot_index >= 0; slot_index--) {
        slot_type = owner->slots[slot_index].type;
        if (slot_type == match_type) {
            owner->slots[slot_index].type = 0;
            owner->slots[slot_index].value = 0;
            func_80042BDC(owner, match_type);
        }
    }
}
