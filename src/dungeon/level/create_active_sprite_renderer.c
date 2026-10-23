#include "common.h"
#include "shared/sprite_frame_state.h"
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

extern s32 render_active_sprite_parts_and_shadows(void *, void *, void *);
extern s32 register_node(ObjectNodeHeader *, s32 (*)(void *, void *, void *));

/* SLUS entry17's initialization list calls this constructor with no arguments
 * and ignores v0. No return-value promise is inferred from the final stores. */
void create_active_sprite_renderer(void)
{
    ObjectNodeHeader *node;
    SpriteFrameState *render;

    node = allocate_flagged_object_node(2);
    if (node != 0) {
        render = (MapRenderPrefix *)node->sprite;
        node->update_callback = 0;
        register_node(node, render_active_sprite_parts_and_shadows);
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;
    }
}
