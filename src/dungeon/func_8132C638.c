#include "common.h"

/* Return the stored count and optionally increment it up to 9999. */
s32 func_80173E38(s32 read_only) {
    register u32 high_byte;
    register u32 low_byte;
    u32 shifted;
    register u16 count;

    {
        u8 *addr = (u8 *)0x80010000;
        high_byte = addr[0x3610];
        low_byte = addr[0x3611];
    }
    shifted = high_byte << 8;
    count = low_byte | shifted;

    if (read_only == 0) {
        if (count < 9999U) {
            if (low_byte < 255U) {
                low_byte++;
            } else {
                low_byte = 0;
                high_byte++;
            }
        }
        {
            u8 *addr = (u8 *)0x80010000;
            addr[0x3611] = low_byte;
            addr[0x3610] = high_byte;
        }
    }

    return count;
}
