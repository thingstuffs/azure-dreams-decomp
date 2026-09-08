#include "common.h"

typedef struct {
    s8 type;
    s8 value;
} S_80042518_Slot;

typedef struct {
    u8 pad[0x2C];
    S_80042518_Slot slot[4];
} S_80042518;

/* Clear the last slot of the requested type and return its value, or zero if absent. */
s32 findSlotByType(S_80042518 *slots, s8 type) {
    s32 slot_index;

    for (slot_index = 3; slot_index >= 0; slot_index--) {
        if (slots->slot[slot_index].type == type) {
            s32 value = slots->slot[slot_index].value;
            slots->slot[slot_index].type = 0;
            slots->slot[slot_index].value = 0;
            return value;
        }
    }
    return 0;
}
