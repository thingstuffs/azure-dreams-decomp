#include "common.h"
#include "shared/object_flags.h"

extern u16 D_80026326;


typedef struct {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set completion flags when red falls below eight. */
void func_80024D70(u16 *effect_data, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_80026326++;

    red = color->red;
    green = color->green;
    color->red = red - (red >> 3);
    blue = color->blue;
    color->green = green - (green >> 3);
    color->blue = blue - (blue >> 3);

    if (color->red < 8) {
        effect_data[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
