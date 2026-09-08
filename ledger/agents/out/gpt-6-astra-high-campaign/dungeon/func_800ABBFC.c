#include "common.h"

/* Set record flags and negate each x coordinate when flag 4 is set. */
void func_800B135C(u8 *record, s32 flags) {
    s32 record_flags = flags;
    u8 *record_x;
    flags &= 4;
    record_x = record + 2;

    for (;;) {
        record[0] = (u8)(record[0] | record_flags);
        if (flags != 0) {
            record_x[0] = (u8)(0 - record_x[0]);
        }
        if ((s8)record[0] < 0) {
            return;
        }
        record_x += 0xc;
        record += 0xc;
    }
}
