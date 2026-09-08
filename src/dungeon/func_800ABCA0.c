#include "common.h"

/* Set flags in the second byte of each record through the end marker. */
void func_800B1400(u8 *record, s32 flags) {
    for (;;) {
        record[1] = record[1] | flags;
        if ((s8)record[0] < 0) {
            return;
        }
        record += 12;
    }
}
