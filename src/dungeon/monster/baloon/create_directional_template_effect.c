#include "dungeon/monster/baloon.h"
#include "shared/object_node.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad_00[0x96];
    s16 ticks;
    u8 pad_98[0x12];
    s16 duration;
    u8 pad_AC[4];
    BaloonTemplateAnchor *anchor;
} BaloonTemplateWork;

typedef struct {
    ObjectNodeHeader header;
    BaloonTemplateWork work;
} BaloonTemplateNode;

extern void *allocate_list_node(s32, ObjectNodeHeader **);
extern void register_node(void *, void *);
extern void project_sprite_chain(void);
extern void select_sprite_entry(SpriteFrameState *, u8, s32);
extern u8 D_800D6FEC[];
extern u8 D_800E23C8[];

/* Copy a gray directional sprite effect and anchor it above the source. */
void create_directional_template_effect(void *unused, BaloonTemplateAnchor *anchor,
    SpriteFrameState *object_template, BaloonTemplateFacing *facing_source)
{
    BaloonTemplateNode *object;
    SpriteFrameState *sprite;
    BaloonTemplateWork *work;
    ObjectPosition *position;

    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        work = &object->work;
        work->ticks = 4;
        work->duration = 4;
        object->header.update_callback = D_800D6FEC;
        work->anchor = anchor;
        sprite = object->header.sprite;
        *sprite = *object_template;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->tpage_abr = 0x20;
        sprite->clut = 0xFF80;
        sprite->depth_bias = -6;
        sprite->flags |= 0xC;
        register_node(object, project_sprite_chain);
        {
            u8 *frames = D_800E23C8;
            sprite->frameTable = frames;
            select_sprite_entry(sprite,
                frames[((g_game_work.view.camera_rotation.parts.viewAngle + facing_source->facing + 0x100) >> 9) & 7], 0);
        }
        position = object->header.position;
        position->x.w.i = anchor->x;
        position->y.w.i = anchor->y;
        position->z.w.i = anchor->z + anchor->height;
    }
}
