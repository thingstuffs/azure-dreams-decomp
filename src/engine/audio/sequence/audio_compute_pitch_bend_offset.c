#include "common.h"

typedef struct {
    u8 pad[0x20];
    u8 unk20;
    u8 unk21;
} S_800565D8;

/* Computes a signed 16-bit value using separate scales below and above 0x40. */
s32 audio_compute_pitch_bend_offset(S_800565D8 *scales, u32 level)
{
    s32 result;
    s32 delta;

    if (level < 0x40) {
        if (scales->unk21 == 0) {
            return 0;
        }
        result = -((scales->unk21 << 1) * (0x3F - level));
    } else if (level == 0x40) {
        return 0;
    } else {
        s32 positive_result;

        delta = level - 0x40;
        if (scales->unk20 == 0) {
            return 0;
        }
        positive_result = scales->unk20;
        positive_result *= 2;
        positive_result *= delta;
        result = positive_result;
    }
    return (s16)result;
}
