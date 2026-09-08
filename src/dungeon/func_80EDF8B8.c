#include "common.h"

#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))

void func_801710B8(void *arg0, void *arg1)
{
    s32 delta;
    s32 value;

    S32_AT(arg1, 0x0) += S32_AT(arg0, 0x40);
    S32_AT(arg1, 0x4) += S32_AT(arg0, 0x44);
    S32_AT(arg1, 0x8) += S32_AT(arg0, 0x48);

    S32_AT(arg0, 0x40) += S32_AT(arg0, 0x4c);
    S32_AT(arg0, 0x44) += S32_AT(arg0, 0x50);
    S32_AT(arg0, 0x48) += S32_AT(arg0, 0x54);

    if (S32_AT(arg0, 0x40) > 0x40000) {
        S32_AT(arg0, 0x40) = 0x40000;
    }
    if (S32_AT(arg0, 0x40) < -0x40000) {
        S32_AT(arg0, 0x40) = -0x40000;
    }
    if (S32_AT(arg0, 0x44) > 0x40000) {
        S32_AT(arg0, 0x44) = 0x40000;
    }
    if (S32_AT(arg0, 0x44) < -0x40000) {
        S32_AT(arg0, 0x44) = -0x40000;
    }
    if (S32_AT(arg0, 0x48) > 0x40000) {
        S32_AT(arg0, 0x48) = 0x40000;
    }
    if (S32_AT(arg0, 0x48) < -0x40000) {
        S32_AT(arg0, 0x48) = -0x40000;
    }

    if (S16_AT(arg0, 0x5a) > S16_AT(arg1, 0x2)) {
        delta = S16_AT(arg0, 0x5a) - S16_AT(arg1, 0x2);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x4c) = (delta >= 17) ? 0x10000 : 0x1000;
    } else {
        delta = S16_AT(arg0, 0x5a) - S16_AT(arg1, 0x2);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x4c) = (delta >= 17) ? -0x10000 : -0x1000;
    }

    if (S16_AT(arg0, 0x5e) > S16_AT(arg1, 0x6)) {
        delta = S16_AT(arg0, 0x5e) - S16_AT(arg1, 0x6);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x50) = (delta >= 17) ? 0x10000 : 0x1000;
    } else {
        delta = S16_AT(arg0, 0x5e) - S16_AT(arg1, 0x6);
        if (delta < 0) {
            delta = -delta;
        }
        S32_AT(arg0, 0x50) = (delta >= 17) ? -0x10000 : -0x1000;
    }

    if (S16_AT(arg0, 0x62) > S16_AT(arg1, 0xa)) {
        delta = S16_AT(arg0, 0x62) - S16_AT(arg1, 0xa);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 17) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            value = 0x10000;
        } else {
            value = 0x1000;
        }
    } else {
        delta = S16_AT(arg0, 0x62) - S16_AT(arg1, 0xa);
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 17) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            value = -0x10000;
        } else {
            value = -0x1000;
        }
    }
    S32_AT(arg0, 0x54) = value;
}
