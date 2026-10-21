#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C5214_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA8];
    s32 unk_BC;
} S_800C5214_0;   /* object in create_user_data_object_b */

extern s32 register_node();
extern u8 D_800345B8[];
extern u8 D_800C52D0[];
extern u8 D_800F148C[];

/* Allocates an object and initializes its display part and user data. */
void *create_user_data_object_b(s32 user_data)
{
    SpriteFrameState *part;
    S_800C5214_0 *object;

    object = allocate_flagged_object_node(0x136);
    if (object == NULL) {
        return NULL;
    }

    {
        register void *return_object;
        register u16 flags;
        register s32 part_value;

        object->unk_10 = D_800C52D0;
        object->unk_BC = user_data;
        part = object->unk_0C;
        part->scale_y = 0x1800;
        part->scale_x = 0x1800;
        part->color.c.b = 0x4C;
        part->color.c.g = 0x4C;
        part->color.c.r = 0x4C;
        part->source = D_800F148C;
        part->unk_00 = 0;
        part->unk_04 = 0;
        part->unk_05 = 0;
        part->unk_06 = -0x10;
        register_node(object, D_800345B8);
        return_object = object;
        flags = part->flags;
        part_value = 0x20;
        part->tpage_abr = part_value;
        part->flags = flags | 0x1C;
        return return_object;
    }
}
