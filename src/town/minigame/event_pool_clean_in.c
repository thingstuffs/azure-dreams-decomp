#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "engine/node.h"

#ifndef NULL
#define NULL 0
#endif


short SD_Call(int flags);
extern M2C_UNK D_8007789C;
extern void D_800BEBA4();

/* event_pool_clean_in: creates the pool cleaning object and initializes its motion and display. */
s32 event_pool_clean_in(void)
{
    ObjectPosition *origin;
    s32 color;
    s32 *motion;
    s32 origin_z;
    ObjectNodeHeader *object;
    SpriteFrameState *object_part;
    void *body;

    object = allocate_flagged_object_node(0x136);
    if (object != NULL) {
        SD_Call(0x512);
        motion = object->position;
        object->update_callback = &D_800BEBA4;
        body = (u8 *)object + 0x20;
        register_node(object, project_sprite_chain);
        ((EntityRec *)body)->x.w.i = 0x10;
        color = 0x00800000;
        motion[0] = view_reference_entity.x.v;
        origin = &view_reference_entity;
        motion[1] = origin->y.v;
        color |= 0x8080;
        origin_z = origin->z.v;
        motion[3] = 0x100000;
        motion[5] = 0xFFF00000;
        motion[2] = origin_z + 0xFFA00000;
        object_part = object->sprite;
        object_part->scale_y = 0x1000;
        object_part->scale_x = 0x1000;
        object_part->source = &D_8007789C;
        object_part->color.word = color;
    }
    return 0;
}
