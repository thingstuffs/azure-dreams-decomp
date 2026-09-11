#include "common.h"

extern s32 D_80083E98[];

/* Counts nonzero entries across five records. */
s32 func_80022160(void) {
    s32 *record;
    s32 record_index;
    s32 active_count;

    do {
        active_count = 0;
    } while (0);
    record_index = active_count;
    record = D_80083E98;
    while (record_index < 5) {
        if (*record != 0) {
            active_count += 1;
        }
        record_index += 1;
        record += 0x20;
    }
    return active_count;
}
