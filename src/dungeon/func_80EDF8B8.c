#include "common.h"

#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))

/* Advance position, clamp velocity, and steer acceleration toward the target. */
void func_801710B8(void *motion, void *position)
{
    s32 target_delta;
    s32 z_accel;

    S32_AT(position, 0x0) += S32_AT(motion, 0x40);
    S32_AT(position, 0x4) += S32_AT(motion, 0x44);
    S32_AT(position, 0x8) += S32_AT(motion, 0x48);

    S32_AT(motion, 0x40) += S32_AT(motion, 0x4c);
    S32_AT(motion, 0x44) += S32_AT(motion, 0x50);
    S32_AT(motion, 0x48) += S32_AT(motion, 0x54);

    if (S32_AT(motion, 0x40) > 0x40000) {
        S32_AT(motion, 0x40) = 0x40000;
    }
    if (S32_AT(motion, 0x40) < -0x40000) {
        S32_AT(motion, 0x40) = -0x40000;
    }
    if (S32_AT(motion, 0x44) > 0x40000) {
        S32_AT(motion, 0x44) = 0x40000;
    }
    if (S32_AT(motion, 0x44) < -0x40000) {
        S32_AT(motion, 0x44) = -0x40000;
    }
    if (S32_AT(motion, 0x48) > 0x40000) {
        S32_AT(motion, 0x48) = 0x40000;
    }
    if (S32_AT(motion, 0x48) < -0x40000) {
        S32_AT(motion, 0x48) = -0x40000;
    }

    if (S16_AT(motion, 0x5a) > S16_AT(position, 0x2)) {
        target_delta = S16_AT(motion, 0x5a) - S16_AT(position, 0x2);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x4c) = (target_delta >= 17) ? 0x10000 : 0x1000;
    } else {
        target_delta = S16_AT(motion, 0x5a) - S16_AT(position, 0x2);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x4c) = (target_delta >= 17) ? -0x10000 : -0x1000;
    }

    if (S16_AT(motion, 0x5e) > S16_AT(position, 0x6)) {
        target_delta = S16_AT(motion, 0x5e) - S16_AT(position, 0x6);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x50) = (target_delta >= 17) ? 0x10000 : 0x1000;
    } else {
        target_delta = S16_AT(motion, 0x5e) - S16_AT(position, 0x6);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        S32_AT(motion, 0x50) = (target_delta >= 17) ? -0x10000 : -0x1000;
    }

    if (S16_AT(motion, 0x62) > S16_AT(position, 0xa)) {
        target_delta = S16_AT(motion, 0x62) - S16_AT(position, 0xa);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        if (target_delta >= 17) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            z_accel = 0x10000;
        } else {
            z_accel = 0x1000;
        }
    } else {
        target_delta = S16_AT(motion, 0x62) - S16_AT(position, 0xa);
        if (target_delta < 0) {
            target_delta = -target_delta;
        }
        if (target_delta >= 17) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            z_accel = -0x10000;
        } else {
            z_accel = -0x1000;
        }
    }
    S32_AT(motion, 0x54) = z_accel;
}
