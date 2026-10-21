#include "common.h"
#include "frontend/card.h"

/* Clears the ten values referenced by the pointer array at offset 0x1D8. */
void card_dev_clear_ten_values(void *state) {
    s32 index;
    u8 *cursor;
    s32 *value;

    cursor = state;
    index = 0;
    do {
        value = *(s32 **)(cursor + 0x1D8);
        *value = 0;
        cursor += 4;
    } while (++index < 10);
}
