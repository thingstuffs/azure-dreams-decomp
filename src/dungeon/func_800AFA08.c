#include "common.h"
#include "shared/object_node.h"

/* The registered constructor initializes only this observed render prefix. */
typedef struct MapRenderPrefix {
    u8 unknown00[0x0C];
    u8 red;
    u8 green;
    u8 blue;
    u8 unknown0F;
    u8 unknown10[0x0C];
    s16 scale_x;
    s16 scale_y;
} MapRenderPrefix;

extern s32 dungeonRenderActiveSpritePartsAndShadows(void *, void *, void *);
extern s32 func_8004491C(ObjectNodeHeader *, s32 (*)(void *, void *, void *));

/* SLUS entry17's initialization list calls this constructor with no arguments
 * and ignores v0. No return-value promise is inferred from the final stores. */
void func_800B5168(void)
{
    ObjectNodeHeader *node;
    MapRenderPrefix *render;

    node = func_8003FC64(2);
    if (node != 0) {
        render = (MapRenderPrefix *)node->unk_0C;
        node->unk_10 = 0;
        func_8004491C(node, dungeonRenderActiveSpritePartsAndShadows);
        render->blue = 0x80;
        render->green = 0x80;
        render->red = 0x80;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;
    }
}
