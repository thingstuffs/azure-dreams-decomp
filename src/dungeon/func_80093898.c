#include "common.h"

extern s32 D_8001029C[];

/* Find the first empty slot and clear its associated table entry. */
s32 func_80098FF8(void) {
    s32 slot_index;
    s32 empty_index;
    s32 *base;

    empty_index = -1;
    for (slot_index = 0; slot_index < 20; slot_index++) {
        if (D_8001029C[slot_index] == 0) {
            empty_index = slot_index;
            break;
        }
    }
    if (empty_index >= 0) {
        base = (s32 *)0x80010000;
        ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        base[empty_index + 0xA8] = 0;
    }
    return (s16)empty_index;
}
