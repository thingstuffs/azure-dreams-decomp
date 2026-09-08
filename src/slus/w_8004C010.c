#include "common.h"

/* CVECTOR-like tint source: r,g,b,cd bytes */
typedef struct S_8004C010 {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} S_8004C010;

/* Apply an RGB tint in place with 7-bit scaling and saturation, skipping neutral tint, and return the color pointer. */
s32 func_8004C010(u8 *color, S_8004C010 *tint)
{
    s32 channelIndex;
    u8 *colorChannel;
    u8 *tintChannel;
    u32 packedTint;

    packedTint = *(u32 *)tint;
    if ((packedTint << 8) == 0x80808000) {
        return (s32)color;
    }

    colorChannel = color;
    tintChannel = (u8 *)tint;
    for (channelIndex = 0; channelIndex < 3;) {
        s32 tintedChannel = (*colorChannel * *tintChannel) >> 7;
        if (tintedChannel < 0x100) {
            *colorChannel = (u8)tintedChannel;
        } else {
            *colorChannel = 0xFF;
        }
        channelIndex++;
        colorChannel++;
        tintChannel++;
    }

    return (s32)color;
}
