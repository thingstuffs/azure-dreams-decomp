#include "common.h"

/* Find the first record with its end marker set. */
s8 *func_800B1484(s8 *record) {
    if (*record >= 0) {
        record += 0xC;
        while (*record >= 0) {
            record += 0xC;
        }
    }
    return record;
}
