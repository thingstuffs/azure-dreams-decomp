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
            goto zero;
        }
        delta = 0x3F - level;
        doubled_scale = scales->unk21;
        do {
            doubled_scale *= 2;
        } while (0);
        scaled_delta = doubled_scale * delta;
        result = -scaled_delta;
        goto sign;
    }

    if (level != 0x40) {
        goto positive;
    }

zero:
    result = 0;
    goto done;

positive:
    {
        register s32 delta ASM_REG("$3");

        delta = level - 0x40;
        if (scales->unk20 == 0) {
            goto zero;
        }
        result = scales->unk20;
        result *= 2;
        result *= delta;
    }

sign:
    result = (s16)result;

done:
    return result;
}
