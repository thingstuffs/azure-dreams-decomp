#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#ifndef NULL
#define NULL 0
#endif

extern void *create_town_effect_object(s32, s32, void *, s32);
extern void *initialize_object_transform_and_state(void *, void *, s32);
extern s32 D_800A6B10;

/* Creates an object and initializes its model scale, color, and flags. */
void create_colored_scaled_effect(s32 object_id) {
    SpriteFrameState *model;
    ObjectNodeHeader *object;

    object = (s8 *) create_town_effect_object(0, object_id, &D_800A6B10, 0);
    if (object != NULL) {
        model = *(s8 * *)&object->sprite;
        initialize_object_transform_and_state(((s8 *)object) + 0x20, model, 0x3A1);
        model->offset_x = 0xC00;
        model->scale_y = 0xC00;
        model->scale_x = 0xC00;
        model->color.c.b = 0xFF;
        model->color.c.g = 0xFF;
        model->color.c.r = 0xFF;
        model->flags = (u16) (model->flags | 0x1C);
    }
}
