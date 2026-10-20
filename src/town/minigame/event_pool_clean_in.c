#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BEAD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800BEAD0_0;

extern s32 register_node();
short SD_Call(int flags);
extern M2C_UNK D_8007789C;
extern M2C_UNK D_800BEBA4;

/* event_pool_clean_in: creates the pool cleaning object and initializes its motion and display. */
s32 event_pool_clean_in(void)
{
    EntityRec *origin;
    s32 color;
    s32 *motion;
    s32 origin_z;
    void *object;
    SpriteFrameState *object_part;
    void *body;

    object = func_8003FC64(0x136);
    if (object != NULL) {
        SD_Call(0x512);
        motion = ((S_800BEAD0_0 *)object)->unk_08;
        ((S_800BEAD0_0 *)object)->unk_10 = &D_800BEBA4;
        body = (u8 *)object + 0x20;
        register_node(object, project_sprite_chain);
        ((EntityRec *)body)->x.w.i = 0x10;
        color = 0x00800000;
        motion[0] = D_80083780.x.v;
        origin = &D_80083780;
        motion[1] = origin->y.v;
        color |= 0x8080;
        origin_z = origin->z.v;
        motion[3] = 0x100000;
        motion[5] = 0xFFF00000;
        motion[2] = origin_z + 0xFFA00000;
        object_part = ((S_800BEAD0_0 *)object)->unk_0C;
        object_part->scale_y = 0x1000;
        object_part->scale_x = 0x1000;
        object_part->source = &D_8007789C;
        object_part->color.word = color;
    }
    return 0;
}
