/* Relink of matched dungeon/func_81881DDC; every changed retail word is a paired relocation. */
#define D_800257CE D_80026472
#include "modules/dungeon_ovl_18a0800.h"
#include "common.h"
#include "shared/object_flags.h"




/* Fade the effect color and set completion flags when red falls below eight. */
void func_800248E4(u16 *effect_data, s32 unused, EffectColor *color) {
    u8 red;
    u8 green;
    u8 blue;

    D_80026472[0]++;

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
