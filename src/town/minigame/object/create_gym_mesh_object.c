#include "shared/object_node.h"
#include "slus.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "engine/node.h"
#include "town/minigame/object.h"

#ifndef NULL
#define NULL 0
#endif

/* Create a lit mesh at the supplied gym position and install its rotation callback. */
void create_gym_mesh_object(ObjectPosition *position, s32 mesh_index, void *update, struct GymState *parent) {
    ObjectNodeHeader *object;
    GymMeshWork *work;
    LitMeshSprite *object_data;

    object = allocate_flagged_object_node(0x136);
    if (object != NULL) {
        register_node(object, draw_linked_lit_meshes);
        *object->position = *position;
        object_data = (LitMeshSprite *)object->sprite;
        work = NODE_BODY(object);
        work->parent = parent;
        object->update_callback = update;
        object_data->scale[0] = 0x1000;
        object_data->scale[1] = 0x1000;
        object_data->scale[2] = 0x1000;
        object_data->clut = 0;
        object_data->flags = 0;
        object_data->tpage_abr = 0;
        object_data->rotation[0] = 0;
        object_data->rotation[1] = 0;
        object_data->rotation[2] = 0;
        object_data->frame_entry = 0;
        object_data->frame_index = 0;
        object_data->frame_ticks = 0;
        object_data->depth_bias = 0xA;
        object_data->color.word = 0x808080;
        object_data->mesh_index = mesh_index;
    }
}
