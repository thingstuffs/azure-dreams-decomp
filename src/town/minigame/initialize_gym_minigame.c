#include "shared/object_node.h"
#include "town/minigame.h"
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
s32 initialize_gym_minigame(void)
{
    s32 position[6];
    s32 object_or_slot;
    void *parent_link;
    SpriteFrameState *render_record;
    void *shared_data;
    void *object_data;
    s32 count;
    u16 *count_page;

    parent_link = NULL;
    shared_data = &D_80020054;
    count_page = (u16 *)0x80010000;
    count = (s16)*(count_page + (0x35C2 / 2));
    if (count < 20) {
        *(count_page + (0x35C2 / 2)) = 20;
    }

    object_or_slot = (s32)allocate_flagged_object_node(2);
    if (object_or_slot != 0) {
        parent_link = NODE_BODY((ObjectNodeHeader *)object_or_slot);
        ((ObjectNodeHeader *)object_or_slot)->update_callback = &D_80022F60;
    }

    position[0] = 0x03800000;
    position[1] = 0x02600000;
    position[2] = (s32)0xFFA00000;
    create_gym_mesh_object(position, 0x34, rotate_gym_mesh_y, parent_link);

    position[2] = (s32)0xFFE00000;
    for (object_or_slot = 3; object_or_slot >= 0; object_or_slot--) {
        if ((object_or_slot >> 1) != 0) {
            position[0] = 0x02700000;
        } else {
            position[0] = 0x04900000;
        }
        if (object_or_slot & 1) {
            position[1] = 0x02E00000;
        } else {
            position[1] = 0x03E00000;
        }
        create_gym_mesh_object(position, 0x35, (u8 *)rotate_gym_mesh_y + 0x14, parent_link);
    }

    object_or_slot = (s32)allocate_flagged_object_node(0x136);
    if (object_or_slot != 0) {
        ((ObjectNodeHeader *)object_or_slot)->update_callback = &D_800240B0;
        object_data = NODE_BODY((ObjectNodeHeader *)object_or_slot);
        register_node((void *)object_or_slot, project_sprite_chain);

        render_record = ((ObjectNodeHeader *)object_or_slot)->sprite;
        render_record->scale_y = 0x1000;
        render_record->scale_x = 0x1000;
        render_record->source = &gym_sprite_source;
        render_record->unk_04 = 0;
        render_record->frame_ticks = 0;
        render_record->color.word = 0x00808080;
        *(void **)((u8 *)object_data + 0x4C) = shared_data;

        configure_the_set_mode_n_3((u8 *)object_or_slot + 0x24,
                      ((ObjectNodeHeader *)object_or_slot)->position,
                      &D_80026F0C);

        ((IntVector3 *)(((ObjectNodeHeader *)object_or_slot)->position))->x = 0x03800000;
        ((IntVector3 *)(((ObjectNodeHeader *)object_or_slot)->position))->y = 0x03C00000;
        ((IntVector3 *)(((ObjectNodeHeader *)object_or_slot)->position))->z = 0;
        *(void **)NODE_BODY((ObjectNodeHeader *)object_or_slot) = parent_link;
    }

    return 0;
}
