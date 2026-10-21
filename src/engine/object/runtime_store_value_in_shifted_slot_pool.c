#include "common.h"

#include "common.h"
#include "engine/object.h"

typedef struct {
    u8 pad_00[0x48];
    s32 slots[15];
} RuntimeState;

extern RuntimeState runtime_script_state;
extern s32 script_status[];

/* Stores a value in the first empty runtime slot, shifting slots when full. */
void runtime_store_value_in_shifted_slot_pool(s32 value) {
    s32 slot_index;

    for (slot_index = 10; slot_index < 15; slot_index++) {
        if (runtime_script_state.slots[slot_index] == 0) {
            runtime_script_state.slots[slot_index] = value;
            if (slot_index != 14) {
                runtime_script_state.slots[slot_index + 1] = 0;
            }
            return;
        }
    }

    for (slot_index = 11; slot_index < 14; slot_index++) {
        runtime_script_state.slots[slot_index] = runtime_script_state.slots[slot_index + 1];
    }
    script_status[0] = value;
}
