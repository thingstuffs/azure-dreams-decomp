#include "common.h"

/* Returns the index of a matching address in a four-byte stride range, or -1. */
s32 func_8009F750(s32 target_addr, s32 slot_addr, s32 slot_count) {
    s32 slot_index;

    slot_index = 0;
    if (slot_count > 0) {
next_slot:
        if (target_addr == slot_addr) {
            return slot_index;
        }
        slot_index += 1;
        if (slot_index < slot_count) {
            slot_addr += 4;
            goto next_slot;
        }
    }
    return -1;
}
