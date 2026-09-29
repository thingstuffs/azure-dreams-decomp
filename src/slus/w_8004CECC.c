#include "common.h"

/* Convert HSV with 0x600 hue units per revolution to RGB bytes. */
u8 *func_8004CECC(u32 hue, s32 saturation, s32 value, u8 *out)
{
    u8 *rgb = out;
    s32 channel_min;
    s32 channel_fall;
    s32 channel_rise;
    s32 sat_byte;
    u32 sector;
    s32 hue_frac;
    register s32 channel_max ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    channel_max = value;

    if ((saturation << 16) == 0) {
        rgb[0] = channel_max;
        rgb[1] = channel_max;
        rgb[2] = channel_max;
    } else {
        channel_max = (0xFF) & (value);
        sat_byte = saturation & 0xFF;
        channel_min = (channel_max * (0xFF00 - (sat_byte << 8)) + 0x7F80) / 0xFF00;
        hue = hue % 0x600;
        sector = hue >> 8;
        hue_frac = hue & 0xFF;
        channel_fall = (channel_max * (0xFF00 - sat_byte * hue_frac) + 0x7F80) / 0xFF00;
        channel_rise = (channel_max * (0xFF00 - sat_byte * (0x100 - hue_frac)) + 0x7F80) / 0xFF00;

        switch (sector) {
        case 0:
            rgb[0] = channel_max;
            rgb[1] = channel_rise;
            rgb[2] = channel_min;
            break;
        case 1:
            rgb[0] = channel_fall;
            rgb[1] = channel_max;
            rgb[2] = channel_min;
            break;
        case 2:
            rgb[0] = channel_min;
            rgb[1] = channel_max;
            rgb[2] = channel_rise;
            break;
        case 3:
            rgb[0] = channel_min;
            rgb[1] = channel_fall;
            rgb[2] = channel_max;
            break;
        case 4:
            rgb[0] = channel_rise;
            rgb[1] = channel_min;
            rgb[2] = channel_max;
            break;
        case 5:
            rgb[0] = channel_max;
            rgb[1] = channel_min;
            rgb[2] = channel_fall;
        }
    }
    return rgb;
}
