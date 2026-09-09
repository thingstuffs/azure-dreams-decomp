#include "common.h"

/* Finds a value in the table, stopping at a zero entry or after 20 entries. */
s32 func_8009904C(s32 target_value) {
    s32 *entry;
    register s32 entry_index ASM_REG("$3") = 0;
    s32 value;

    entry = (s32 *)0x80010000;
loop:
    value = entry[0xA7];
    if (value != 0) {
        if (value != target_value) {
            entry_index++;
            entry++;
            if (entry_index < 20) {
                goto loop;
            }
        } else {
            return (s16)entry_index;
        }
    }
    return -1;
}
