#include "common.h"

extern s32 D_800CF720[];

/* Sum the second word of each requested table entry. */
s32 func_8008ACE8(s32 entry_count) {
    s32 *entry;
    s32 sum;
    s32 i;

    sum = 0;
    for (i = 0; i < entry_count; i++) {
        entry = &D_800CF720[i * 2];
        sum += entry[1];
    }
    return sum;
}
