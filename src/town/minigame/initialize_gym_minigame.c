#include "shared/object_node.h"
#include "town/minigame.h"
#include "town/minigame/gym.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/vector.h"
#include "engine/node.h"
#include "town/minigame/object.h"
#include "town/scene.h"
#include "town/data.h"

#define NULL ((void *)0)

extern s32 D_80020054;
extern s32 D_80022F60;

extern s32 D_800240B0;
extern s32 D_80026F0C;

/* Creates linked town objects at fixed positions and initializes their display data. */
/* The dispatcher passes four explicit zero arguments. */
s32 initialize_gym_minigame(s32 unused_arg0, s32 unused_arg1, s32 unused_arg2, s32 unused_arg3)
{
    ObjectPosition position;
    ObjectNodeHeader *node;
    s32 slot;
    GymState *parent_link;
    SpriteFrameState *render_record;
    s32 *shared_data;
    GymPhaseSpriteBody *object_data;
    s32 count;
    u16 *count_page;

    parent_link = NULL;
    shared_data = &D_80020054;
    count_page = (u16 *)0x80010000;
    count = (s16)*(count_page + (0x35C2 / 2));
    if (count < 20) {
        *(count_page + (0x35C2 / 2)) = 20;
    }

    node = allocate_flagged_object_node(2);
    if (node != 0) {
        parent_link = NODE_BODY(node);
        node->update_callback = &D_80022F60;
    }

    position.x.v = 0x03800000;
    position.y.v = 0x02600000;
    position.z.v = (s32)0xFFA00000;
    create_gym_mesh_object(&position, 0x34, rotate_gym_mesh_y, parent_link);

    position.z.v = (s32)0xFFE00000;
    for (slot = 3; slot >= 0; slot--) {
        if ((slot >> 1) != 0) {
            position.x.v = 0x02700000;
        } else {
            position.x.v = 0x04900000;
        }
        if (slot & 1) {
            position.y.v = 0x02E00000;
        } else {
            position.y.v = 0x03E00000;
        }
        create_gym_mesh_object(&position, 0x35, (u8 *)rotate_gym_mesh_y + 0x14, parent_link);
    }

    node = allocate_flagged_object_node(0x136);
    if (node != 0) {
        node->update_callback = &D_800240B0;
        object_data = NODE_BODY(node);
        register_node(node, project_sprite_chain);

        render_record = node->sprite;
        render_record->scale_y = 0x1000;
        render_record->scale_x = 0x1000;
        render_record->source = &gym_sprite_source;
        render_record->unk_04 = 0;
        render_record->frame_ticks = 0;
        render_record->color.word = 0x00808080;
        object_data->shared_data = shared_data;

        init_scene_node_mode_3(&object_data->scene_node,
                      node->position,
                      &D_80026F0C);

        node->position->x.v = 0x03800000;
        node->position->y.v = 0x03C00000;
        node->position->z.v = 0;
        object_data->controller = parent_link;
    }

    return 0;
}
