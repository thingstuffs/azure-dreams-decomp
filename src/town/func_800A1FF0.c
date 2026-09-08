#include "common.h"

/* Returns the index of an address in a range of four-byte slots, or -1. */
s32 func_8009F750(s32 target_addr, s32 slot_addr, s32 slot_count) {
    s32 slot_index;

    slot_index = 0;
    if (slot_count > 0) {
        while (1) {
            if (target_addr == slot_addr) {
                return slot_index;
            }
            slot_index += 1;
            if (slot_index >= slot_count) {
                break;
            }
            slot_addr += 4;
        }
    }
    return -1;
}
