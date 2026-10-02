#include "common.h"
s32 func_8009904C(s32 target_value) {
    s32 *table = (s32 *)0x80010000;
    s32 entry_index;
    for (entry_index = 0; entry_index < 20; entry_index++) {
        if (table[167 + entry_index] == 0)
            break;
        if (table[167 + entry_index] == target_value)
            return (s16)entry_index;
    }
    return -1;
}
