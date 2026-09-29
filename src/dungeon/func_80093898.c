#include "common.h"

/* Find the first empty slot and clear its associated table entry. */
s32 func_80098FF8(void) {
    s32 slot_index;
    s32 empty_index;
    s32 *base;

    base = (s32 *)0x80010000;
    empty_index = -1;
    for (slot_index = 0; slot_index < 20; slot_index++) {
        if (base[slot_index + 0xA7] == 0) {
            empty_index = slot_index;
            break;
        }
    }
    if (empty_index >= 0) {
        base[empty_index + 0xA8] = 0;
    }
    return (s16)empty_index;
}
