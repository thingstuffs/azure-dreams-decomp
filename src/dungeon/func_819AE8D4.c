#include "modules/dungeon_ovl_19cc800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"


/* Colour bytes of the effect's render data. */
typedef struct EffectColor {
    u8 pad[12];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

/* Fade the effect color and set flags when red falls below four. */
void fade_effect_color_to_black(void *record, s32 unused, EffectColor *color) {
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
        ((ObjectNodeHeader *)record - 1)->flags |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

