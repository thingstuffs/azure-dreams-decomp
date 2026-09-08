#include "common.h"

extern s32 D_80083E98[];

/* Counts nonzero entries across five records. */
s32 func_80022160(void) {
    s32 *record;
    register s32 record_index ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 active_count;

    active_count = 0;
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
