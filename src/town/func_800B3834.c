#include "common.h"

/* Check whether the entry passes the type and flag filter. */
s32 func_800B0F94(void *entry) {
    u8 flags;
    u8 value;

    value = *((u8 *)entry + 1);
    if (value == 0x16) {
        return 0;
    }
    if (value == 0x19) {
        flags = *((u8 *)entry + 3);
        if (flags & 8) {
            return 0;
        }
    }
    return 1;
}
