#include "shared/object_node.h"
#include "slus.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/node.h"
#include "town/minigame/object.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80022E64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    struct GymState *unk_20;
} S_80022E64_0;   /* obj in create_gym_mesh_object */

typedef struct Copy24 {
    s32 word[6];
} Copy24;

/* Allocates an object, copies six source words, and initializes its data. */
void create_gym_mesh_object(void *source_words, s32 data_value_08, s32 object_value_10, struct GymState *object_value_20) {
    S_80022E64_0 *object;
    Copy24 *copy_dst;
    SpriteFrameState *object_data;

    object = allocate_flagged_object_node(0x136);
    if (object != NULL) {
        register_node(object, draw_linked_lit_meshes);
        copy_dst = object->unk_08;
        *copy_dst = *(Copy24 *)source_words;
        object_data = object->unk_0C;
        object->unk_20 = object_value_20;
        object->unk_10 = object_value_10;
        object_data->scale_x = 0x1000;
        object_data->scale_y = 0x1000;
        object_data->offset_x = 0x1000;
        object_data->clut = 0;
        object_data->flags = 0;
        object_data->tpage_abr = 0;
        object_data->angle_x = 0;
        object_data->angle_y = 0;
        object_data->angle_z = 0;
        object_data->unk_00 = 0;
        object_data->unk_04 = 0;
        object_data->frame_ticks = 0;
        object_data->depth_bias = 0xA;
        object_data->color.word = 0x808080;
        object_data->source = data_value_08;
    }
}
