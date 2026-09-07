#include "common.h"

extern void *jtbl_8002E5F8[];

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
    register s32 channel_max ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    static void *const keepalive[] = {
        &&L_case_0, &&L_case_1, &&L_case_2,
        &&L_case_3, &&L_case_4, &&L_case_5
    };
    (void)keepalive;

    ASM_KEEP(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    channel_max = value;

    if ((saturation << 16) == 0) {
        rgb[0] = channel_max;
        rgb[1] = channel_max;
        rgb[2] = channel_max;
        goto done;
    }

    channel_max = value & 0xFF;
    sat_byte = saturation & 0xFF;
    channel_min = (channel_max * (0xFF00 - (sat_byte << 8)) + 0x7F80) / 0xFF00;
    hue = hue % 0x600;
    hue_frac = hue & 0xFF;
    channel_fall = (channel_max * (0xFF00 - sat_byte * hue_frac) + 0x7F80) / 0xFF00;
    channel_rise = (channel_max * (0xFF00 - sat_byte * (0x100 - hue_frac)) + 0x7F80) / 0xFF00;
    sector = hue >> 8;

    if (sector >= 6) {
        goto after_switch;
    }
    goto *jtbl_8002E5F8[sector];

L_case_0:
    rgb[0] = channel_max;
    rgb[1] = channel_rise;
    rgb[2] = channel_min;
    goto after_switch;
L_case_1:
    rgb[0] = channel_fall;
    rgb[1] = channel_max;
    rgb[2] = channel_min;
    goto after_switch;
L_case_2:
    rgb[0] = channel_min;
    rgb[1] = channel_max;
    rgb[2] = channel_rise;
    goto after_switch;
L_case_3:
    rgb[0] = channel_min;
    rgb[1] = channel_fall;
    rgb[2] = channel_max;
    goto after_switch;
L_case_4:
    rgb[0] = channel_rise;
    rgb[1] = channel_min;
    rgb[2] = channel_max;
    goto after_switch;
L_case_5:
    rgb[0] = channel_max;
    rgb[1] = channel_min;
    rgb[2] = channel_fall;
after_switch:
    ASM_KEEP(sector);   /* MATCH pin: slus-diff */
done:
    return rgb;
}
