#include "common.h"

/* Return the index of the requested zero-based matching occurrence, or -1. */
s32 func_80026EC0(s32 target_value, s32 target_occurrence) {
    s32 occurrence;
    s32 index;
    u8 *page = (u8 *)0x80010000;

    occurrence = 0;
    for (index = 0; index < 0x40; index++) {
        if (page[0x57D2 + index * 0x13] == target_value) {
            if (occurrence == target_occurrence) {
                return index;
            }
            occurrence++;
        }
    }
    return -1;
}
