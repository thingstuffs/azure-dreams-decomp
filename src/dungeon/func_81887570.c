#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

extern u16 D_80026326;



/* Retail 81887570 (dungeonHandleRetailN81887570Callee80024D70FadeColourN1N8PerCallMark): fade the colour by 1/8 per call and mark the effect (header and global
 * flags) finished once red falls below eight.  effect is the effect's record; its header precedes it. */
void dungeonHandleRetailN81887570Callee80024D70FadeColourN1N8PerCallMark(void *effect, s32 unused, EffectColor *color) {
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
        ((ObjectNodeHeader *)effect - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
