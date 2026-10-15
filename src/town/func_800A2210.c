#include "common.h"

/* Find the first vacant record among count records of size 0x54. */
s32 func_8009F970(const u8 *records, s32 count) {
    s32 index;
    for (index = 0; index < count; index++, records += 0x54) {
        if (records[0x13] == 0) {
            return index;
        }
    }
    return -1;
}
