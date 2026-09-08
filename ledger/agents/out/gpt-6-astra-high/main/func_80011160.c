#include "common.h"

/* Clear the ten values referenced by the pointer table at offset 0x25C. */
void func_80024160(void *object) {
    s32 slot;
    u8 *cursor;
    s32 *value;

    cursor = object;
    slot = 0;
    do {
        value = *(s32 **)(cursor + 0x25C);
        asm volatile("" : : "r"(value));
        *value = 0;
        slot++;
        cursor += 4;
    } while (slot < 10);
}
