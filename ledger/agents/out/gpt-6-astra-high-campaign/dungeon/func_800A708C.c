#include "common.h"

/* Tests flag 0x08000000 and propagates flag 0x40000 when it is set. */
s32 func_800AC7EC(s32 unused_0, s32 unused_1, s32 unused_2, s32 *record) {
    s32 flags = record[7];

    if (flags & 0x08000000) {
        if (record[5] & 0x40000) {
            record[7] = flags | 0x40000;
        }
        return 1;
    }
    return 0;
}
