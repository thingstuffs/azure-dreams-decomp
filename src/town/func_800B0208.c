#include "common.h"

/* Count nonzero words in the fixed table until its zero terminator. */
s32 func_800AD968(void) {
    volatile s32 *entry;
    s32 count;

    entry = (volatile s32 *)0x8001029C;
    count = 0;
    if (entry[0] != 0) {
        do {
            entry = entry + 1;
            count++;
        } while (entry[0] != 0);
    }
    return count;
}
