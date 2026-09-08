#include "common.h"

extern u8 initialStatsTable[24];

s32 func_8002773C(u8 *arg0) {
    s32 outer;
    s32 value;
    register s32 inner ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 group;
    u8 *stats;
    u8 *entry;
    u8 entry_value;

    outer = 0;
    stats = initialStatsTable + (arg0[0x13] * 24);
    do {
        value = stats[8] & 0x7F;
        if ((value != 0) && (value < 46)) {
            inner = 0;
            entry = arg0;
            group = (value - 1) / 3;
            do {
                entry_value = entry[8];
                if ((entry_value != 0) &&
                    (group == ((entry_value - 1) / 3))) {
                    return (s16)inner;
                }
                inner += 1;
                entry += 3;
            } while (inner < 3);
        }
        outer += 1;
        stats += 3;
    } while (outer < 3);
    return -1;
}
