#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "slus.h"
#include "common.h"
#include "shared/object_flags.h"
#include "engine/node.h"
#include "town/minigame.h"
#include "town/scene.h"
#include "town/minigame/object.h"

#ifndef NULL
#define NULL 0
#endif



extern u8 D_800D2348[];
extern s32 D_800D2360;

/* Initialize an object and its packet, then set the caller and global flags. */
void spawn_state_position_object(TownObjectRecord *caller_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    ObjectNodeHeader *obj;
    LitMeshSprite *part;
    ObjectStatePositionObject *setup;
    ObjectPosition *position;

    obj = allocate_flagged_object_node(0x136);
    if (obj != NULL) {
        register_node(obj, draw_linked_lit_meshes);
        obj->update_callback = update_proximity_triggered_object;
        part = (LitMeshSprite *)obj->sprite;
        part->scale[0] = 0x1000;
        part->scale[1] = 0x1000;
        part->scale[2] = 0x1000;
        part->color.word = 0x808080;
        setup = NODE_BODY(obj);
        part->rotation[2] = 0;
        part->mesh_index = 0x60;
        position = obj->position;
        position->x.v = 0x05400000;
        position->y.v = 0x02300000;
        position->z.v = 0;
        setup->setup_value = D_800D2360;
        init_scene_node_mode_1(setup, position, D_800D2348);
    }
    NODE_HEADER(caller_data)->flags |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
