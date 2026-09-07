#include "common.h"

void func_800B3B18(u8 *arg0)
{
    s32 delta;
    s32 magnitude;
    s32 adjusted;
    u8 value;

    if ((*(u32 *)arg0 << 8) == 0x80808000) {
        return;
    }

    value = arg0[0];
    delta = 0x80 - value;
    magnitude = delta;
    if (delta < 0) {
        ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted = delta;
        if (adjusted < 0) {
            adjusted += 3;
        }
        arg0[0] = value + (adjusted >> 2);
    } else {
        arg0[0] = 0x80;
    }

    value = arg0[1];
    delta = 0x80 - value;
    magnitude = delta;
    if (delta < 0) {
        ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted = delta;
        if (adjusted < 0) {
            adjusted += 3;
        }
        arg0[1] = value + (adjusted >> 2);
    } else {
        arg0[1] = 0x80;
    }

    value = arg0[2];
    delta = 0x80 - value;
    magnitude = delta;
    if (delta < 0) {
        ASM_KEEP(magnitude);   /* MATCH pin: retail register colouring depends on it */
        magnitude = 0 - magnitude;
    }
    if (magnitude >= 5) {
        adjusted = delta;
        if (adjusted < 0) {
            adjusted += 3;
        }
        arg0[2] = value + (adjusted >> 2);
    } else {
        arg0[2] = 0x80;
    }
}

/* MECHANISM: True-space CFG recovery makes this a frameless leaf; the three
   apparent callees are local joins. Explicit adjusted-delta live ranges place
   the signed /4 correction in v0, and last-use magnitude keeps preserve each
   retail move-v0-v1 followed by the in-place negu-v0-v0 idiom. */
