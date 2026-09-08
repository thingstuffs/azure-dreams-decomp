#include "common.h"
#include "m2c_compat.h"

typedef struct S_800ADFBC_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800ADFBC_0;   /* var_a0 in func_800ADFBC */

/* Counts four-byte entries until an entry's second byte is zero. */
s32 func_800ADFBC(void *entries) {
    s32 count;
    void *entry;

    entry = entries;
    count = 0;
    if (((S_800ADFBC_0 *)entry)->unk_01 != 0) {
        do {
            entry += 4;
            count += 1;
        } while (((S_800ADFBC_0 *)entry)->unk_01 != 0);
    }
    return count;
}
