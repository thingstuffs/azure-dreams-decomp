#include "common.h"

extern s8 D_800CF720[16];

/* Returns the matching entry index, or the entry count with the high bit set if absent. */
s32 func_8008AD1C(s32 first_byte, s32 second_byte, s32 halfword_value) {
    s32 result;
    s32 entry_index;
    s32 end_marker;
    s32 scan_end_marker;
    s8 *entry_table;
    s8 *entry;

    entry_table = D_800CF720;
    entry_index = 0;
    end_marker = -1;
    if (entry_table[1] != end_marker) {
        scan_end_marker = end_marker;
        entry = entry_table;
check_entry:
        if ((first_byte != entry[0]) || (second_byte != entry[1]) || (halfword_value != *(s16 *)(entry + 2))) {
            entry += 8;
            entry_index += 1;
            if (entry[1] == scan_end_marker) {
                goto not_found;
            }
            goto check_entry;
        }
        result = entry_index;
    } else {
not_found:
        result = entry_index - 0x80000000;
    }
    ASM_USE(result);   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    return result;
}
