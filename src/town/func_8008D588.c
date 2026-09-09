#include "common.h"

extern s32 D_800CF720[];

/* Sum the second word of each requested table entry. */
s32 func_8008ACE8(s32 entry_count) {
    s32 *entry;
    s32 sum;
    s32 i;
    s32 value;

    i = 0;
    do {
        sum = i;
    } while (0);
    if (entry_count > 0) {
        entry = D_800CF720;
        do {
            do {
                value = entry[1];
            } while (0);
            i += 1;
            sum += value;
            entry += 2;
        } while (i < entry_count);
    }
    return sum;
}
