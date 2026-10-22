#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80026ED0_3 {
    u8 pad_00[0x66];
    s16 unk_66;
    u8 pad_68[0x2];
    s16 unk_6A;
} S_80026ED0_3;

extern void *allocate_list_node();
extern s32 register_node();
extern s32 D_80026E3C;
extern s32 D_800DF358;

/* Creates a visual object with the given position and size. */
void *create_visual_object(s16 x, s16 y, s16 z, s32 size) {
    ObjectNodeHeader *object;
    ObjectPosition *position;
    SpriteFrameState *render_data;
    S_80026ED0_3 *effect_data;
    s16 saved_size;

    saved_size = size;

    object = allocate_list_node(0x12, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        object->unk_10 = &D_80026E3C;
        register_node(object, project_sprite_chain);
        position = object->position;
        position->x.w.i = x;
        position->y.w.i = y;
        position->z.w.i = z;
        render_data = object->sprite;
        render_data->source = &D_800DF358;
        render_data->color.word = 0x808080;
        render_data->scale_y = saved_size;
        render_data->scale_x = saved_size;
        render_data->tpage_abr = 0x20;
        render_data->flags |= 0xC;
        effect_data = (u8 *)object + 0x20;
        effect_data->unk_66 = 0x20;
        effect_data->unk_6A = 0x80;
    }
    return object;
}
