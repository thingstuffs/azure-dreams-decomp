#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/actor/object.h"
#include "dungeon/actor/alternating_shade.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_80026E3C;
extern s32 visual_object_sprite_data;

/* Creates a visual object with the given position and size. */
void *create_visual_object(s16 x, s16 y, s16 z, s32 size) {
    ObjectNodeHeader *object;
    ObjectPosition *position;
    SpriteFrameState *render_data;
    AlternatingShadeBody *effect_data;
    s16 saved_size;

    saved_size = size;

    object = allocate_list_node(0x12, &scene_object_list_anchor.next);
    if (object != NULL) {
        object->update_callback = &D_80026E3C;
        register_node(object, project_sprite_chain);
        position = object->position;
        position->x.w.i = x;
        position->y.w.i = y;
        position->z.w.i = z;
        render_data = object->sprite;
        render_data->source = &visual_object_sprite_data;
        render_data->color.word = 0x808080;
        render_data->scale_y = saved_size;
        render_data->scale_x = saved_size;
        render_data->tpage_abr = 0x20;
        render_data->flags |= 0xC;
        effect_data = NODE_BODY(object);
        effect_data->ticks_left = 0x20;
        effect_data->intensity = 0x80;
    }
    return object;
}
