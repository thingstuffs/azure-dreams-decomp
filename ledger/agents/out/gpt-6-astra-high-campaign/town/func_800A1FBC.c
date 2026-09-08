#include "common.h"

/* Return the first free four-byte entry index, or -1 if none is available. */
s32 func_8009F71C(void *entry, s32 entry_count) {
    s32 entry_index = 0;

    if (entry_count > 0) {
        do {
            if (((u8 *)entry)[1] == 0) {
                return entry_index;
            }
            entry_index++;
            entry += 4;
        } while (entry_index < entry_count);
    }
    return -1;
}
