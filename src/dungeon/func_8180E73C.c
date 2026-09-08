#include "common.h"

extern u8 initialStatsTable[24];

/* Finds a record slot matching an initial-stat value group, or returns -1. */
s32 func_8002773C(u8 *record) {
    s32 initial_index;
    s32 initial_value;
    register s32 entry_index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 value_group;
    u8 *initial_entry;
    u8 *entry;
    u8 entry_value;

    initial_index = 0;
    initial_entry = initialStatsTable + (record[0x13] * 24);
    do {
        initial_value = initial_entry[8] & 0x7F;
        if ((initial_value != 0) && (initial_value < 46)) {
            entry_index = 0;
            entry = record;
            value_group = (initial_value - 1) / 3;
            do {
                entry_value = entry[8];
                if ((entry_value != 0) &&
                    (value_group == ((entry_value - 1) / 3))) {
                    return (s16)entry_index;
                }
                entry_index += 1;
                entry += 3;
            } while (entry_index < 3);
        }
        initial_index += 1;
        initial_entry += 3;
    } while (initial_index < 3);
    return -1;
}
