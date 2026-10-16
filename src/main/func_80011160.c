#include "common.h"

/* Clear the ten values referenced by the pointer table at offset 0x25C. */
void cardBootClearTenDisplaySlots(void *object) {
    s32 slot;
    u8 *cursor;
    cursor = object;
    for (slot = 0; slot < 10; slot++) {
        **(s32 **)(cursor + 0x25C) = 0;
        cursor += 4;
    }
}
