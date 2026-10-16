/* Relink of matched town/func_800B0208; every changed retail word is a paired relocation. */
#include "common.h"

/* Count nonzero words in the fixed table until its zero terminator. */
s32 func_800B0718(void) {
    s32 *entry;
    s32 count;

    entry = (s32 *)0x8001029C;
    count = 0;
    if (entry[0] != 0) {
        do {
            entry = entry + 1;
            count++;
        } while (entry[0] != 0);
    }
    return count;
}
