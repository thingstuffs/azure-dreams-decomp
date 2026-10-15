#include "modules/dungeon_ovl_19a332c.h"

void func_80024AB4(u16 *effect_data, s32 unused, ovl_19a332c_819832B4_EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_800269F8++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 2);
    blue = color->blue;
    color->green = green - (green >> 2);
    color->blue = blue - (blue >> 2);

    if (color->red < 4) {
        effect_data[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
