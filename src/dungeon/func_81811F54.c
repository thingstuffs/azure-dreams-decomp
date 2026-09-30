#include "common.h"

/* Return the index of the requested zero-based occurrence matching both bytes, or -1. */
s32 func_80026F54(s32 target_value, s32 prefix_value, s32 target_occurrence)
{
    s32 occurrence;
    s32 index;
    s32 offset;

    occurrence = 0;
    index = occurrence;

    do {
        offset = index * 0x13;
        if ((((u8 *)0x800157C0)[offset + 0x12] == target_value) && (((u8 *)0x800157C0)[offset + 0x11] == prefix_value)) {
            if (occurrence == target_occurrence) {
                return index;
            }
            occurrence++;
        }
        index++;
    } while (index < 0x40);
    return -1;
}
