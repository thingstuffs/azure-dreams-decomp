#include "common.h"

/* Move three channel values a quarter of the way toward 0x80, snapping when within four. */
void func_800B3B18(u8 *channels)
{
    s32 delta;
    s32 magnitude;
    s32 adjusted_delta;
    u8 value;

    if ((*(u32 *)channels << 8) == 0x80808000) {
        return;
    }

    value = channels[0];
    delta = 0x80 - value;
    magnitude = delta;
    if (delta < 0) {
        ASM_KEEP(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted_delta = delta;
        if (adjusted_delta < 0) {
            adjusted_delta += 3;
        }
        channels[0] = value + (adjusted_delta >> 2);
    } else {
        channels[0] = 0x80;
    }

    value = channels[1];
    delta = 0x80 - value;
    magnitude = delta;
    if (delta < 0) {
        ASM_KEEP(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted_delta = delta;
        if (adjusted_delta < 0) {
            adjusted_delta += 3;
        }
        channels[1] = value + (adjusted_delta >> 2);
    } else {
        channels[1] = 0x80;
    }

    value = channels[2];
    delta = 0x80 - value;
    magnitude = delta;
    if (delta < 0) {
        ASM_KEEP(magnitude);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted_delta = delta;
        if (adjusted_delta < 0) {
            adjusted_delta += 3;
        }
        channels[2] = value + (adjusted_delta >> 2);
    } else {
        channels[2] = 0x80;
    }
}
