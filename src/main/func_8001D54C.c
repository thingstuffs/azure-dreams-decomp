#include "common.h"

/* Clears the ten values referenced by the pointer array at offset 0x1D8. */
void func_8001D54C(void *state) {
    s32 index;
    u8 *cursor;
    s32 *value;

    cursor = state;
    index = 0;
    do {
        value = *(s32 **)(cursor + 0x1D8);
        *value = 0;
        index++;
        do {
            cursor += 4;
        } while (0);
    } while (index < 10);
}
