#include "common.h"

typedef struct {
    u8 pad[0x20];
    volatile u8 unk20;
    volatile u8 unk21;
} S_800565D8;

/* Computes a signed 16-bit value using separate scales below and above 0x40. */
s32 func_800565D8(S_800565D8 *scales, u32 level)
{
    s32 result;

    if (level < 0x40) {
        s32 delta;
        s32 doubled_scale;
        s32 scaled_delta;

        if (scales->unk21 == 0) {
            return 0;
        }
        delta = 0x3F - level;
        doubled_scale = scales->unk21;
        do {
            doubled_scale *= 2;
        } while (0);
        scaled_delta = doubled_scale * delta;
        result = -scaled_delta;
        result = (s16)result;
        return result;
    }

    if (level == 0x40) {
zero:
        result = 0;
        return result;
    }

    {
        s32 delta;
        s32 positive_result;
        delta = level - 0x40;
        if (scales->unk20 == 0) {
            goto zero;
        }
        positive_result = scales->unk20;
        positive_result *= 2;
        positive_result *= delta;
        result = positive_result;
        result = (s16)result;
        return result;
    }
}
