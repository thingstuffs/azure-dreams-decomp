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
        ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        *value = 0;
        index++;
        cursor += 4;
    } while (index < 10);
}
