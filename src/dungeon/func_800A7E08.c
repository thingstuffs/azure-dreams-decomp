#include "common.h"

/* Cap and return the adjustment so the base plus adjustment stays within the limit. */
s16 func_800AD568(void *entry) {
    s16 adjustment;
    u8 base;
    u8 limit;
    __typeof__(limit - base) hoisted_1;

    adjustment = *(s16 *)((u8 *)entry + 0x64);
    base = *((u8 *)entry + 0x28);
    limit = *((u8 *)entry + 0x29);
    if ((s32)limit < (adjustment + base)) {
        hoisted_1 = limit - base;
        *(s16 *)((u8 *)entry + 0x64) = (s16)hoisted_1;
    }
    return *(s16 *)((u8 *)entry + 0x64);
}
