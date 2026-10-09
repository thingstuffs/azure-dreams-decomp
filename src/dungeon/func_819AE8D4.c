#include "common.h"
#include "shared/object_flags.h"

extern u16 D_80027452[5];


typedef struct {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set flags when red falls below four. */
void func_800260D4(u16 *effect_data, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_80027452[0]++;

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
