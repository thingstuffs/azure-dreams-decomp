#include "common.h"

s32 func_80173E38(s32 arg0) {
    register u32 hi;
    register u32 lo;
    register u32 shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u32 value;

    {
        register u8 *addr ASM_REG("$2") = (u8 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        hi = addr[0x3610];
        lo = addr[0x3611];
    }
    shifted = hi << 8;
    value = lo | shifted;

    if (arg0 == 0) {
        if (value < 9999U) {
            if (lo < 255U) {
                lo++;
            } else {
                lo = 0;
                hi++;
            }
        }
        {
            u8 *addr = (u8 *)0x80010000;
            addr[0x3611] = lo;
            addr[0x3610] = hi;
        }
    }

    return value & 0xFFFF;
}
