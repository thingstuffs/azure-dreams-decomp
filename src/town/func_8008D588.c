#include "common.h"

extern s32 D_800CF720[];

/* Sum the second word of each requested table entry. */
s32 func_8008ACE8(s32 entry_count) {
    s32 *entry;
    s32 sum;
    register s32 i ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value;

    i = 0;
    sum = i;
    if (entry_count > 0) {
        entry = D_800CF720;
        do {
            value = entry[1];
            ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            i += 1;
            sum += value;
            entry += 2;
        } while (i < entry_count);
    }
    return sum;
}
