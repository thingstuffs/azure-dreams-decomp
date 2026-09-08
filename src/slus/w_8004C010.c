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
    s32 channel_index;
    u8 *color_channel;
    u8 *tint_channel;
    u32 packed_tint;

    packed_tint = *(u32 *)tint;
    if ((packed_tint << 8) == 0x80808000) {
        return (s32)color;
    }

    color_channel = color;
    tint_channel = (u8 *)tint;
    for (channel_index = 0; channel_index < 3;) {
        s32 tinted_channel = (*color_channel * *tint_channel) >> 7;
        if (tinted_channel < 0x100) {
            *color_channel = (u8)tinted_channel;
        } else {
            *color_channel = 0xFF;
        }
        channel_index++;
        color_channel++;
        tint_channel++;
    }

    return (s32)color;
}
