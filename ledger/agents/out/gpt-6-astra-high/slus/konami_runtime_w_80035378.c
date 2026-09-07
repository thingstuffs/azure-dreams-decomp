#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x48];
    s32 slots[15];
} RuntimeState;

extern RuntimeState D_80082A38;
extern s32 D_80082AB8[];

/* Stores a value in the first empty runtime slot, shifting slots when full. */
void func_80035378(s32 value) {
    s32 slot_index;

    for (slot_index = 10; slot_index < 15; slot_index++) {
        if (D_80082A38.slots[slot_index] == 0) {
            D_80082A38.slots[slot_index] = value;
            if (slot_index != 14) {
                D_80082A38.slots[slot_index + 1] = 0;
            }
            return;
        }
    }

    for (slot_index = 11; slot_index < 14; slot_index++) {
        D_80082A38.slots[slot_index] = D_80082A38.slots[slot_index + 1];
    }
    D_80082AB8[0] = value;
}
