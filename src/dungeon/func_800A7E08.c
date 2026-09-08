#include "common.h"

/* Cap and return the adjustment so the base plus adjustment stays within the limit. */
s16 func_800AD568(void *entry) {
    s16 adjustment;
    u8 base;
    u8 limit;

    adjustment = *(s16 *)((u8 *)entry + 0x64);
    base = *((u8 *)entry + 0x28);
    limit = *((u8 *)entry + 0x29);
    if ((s32)limit < (adjustment + base)) {
        *(s16 *)((u8 *)entry + 0x64) = (s16)(limit - base);
    }
    return *(s16 *)((u8 *)entry + 0x64);
}
