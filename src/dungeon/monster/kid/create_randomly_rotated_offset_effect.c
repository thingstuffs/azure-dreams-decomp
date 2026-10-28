#include "shared/sprite_frame_state.h"
#include "dungeon/monster/kid.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "engine/node.h"

typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern s32 rand(void);

extern u8 D_8017520C[12];

typedef struct S_80174800_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
} S_80174800_0;   /* part in create_randomly_rotated_offset_effect */

typedef struct S_80174800_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80174800_1;   /* data in create_randomly_rotated_offset_effect */

typedef struct S_80174800_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80174800_2;   /* pos in create_randomly_rotated_offset_effect */

/* Creates an effect at an offset from the source position with a random rotation. */
/* Creates a randomly rotated Kid sprite 40 units above the source, with the supplied scale and a copied
 * texture entry. */
void create_randomly_rotated_offset_effect(void *unused_ptr, EntityRec *source_pos, s32 unused_value, s16 scale)
{
    ObjectNodeHeader * node;
    S_80174800_0 *part;
    SpriteFrameState *data;
    ObjectPosition *pos;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        part = (u8 *)node + 0x20;
        part->unk_1A = 65;
        (node->update_callback) = animate_effect_colors;
        register_node(node, project_sprite_chain);
        data = node->sprite;
        data->tpage_abr = 0x60;
        data->flags |= 0xC;
        pos = node->position;
        pos->x.w.i = ((u16)source_pos->x.w.i);
        pos->y.w.i = ((u16)source_pos->y.w.i);
        pos->z.w.i = ((u16)source_pos->z.w.i) - 0x28;
        data = node->sprite;
        data->depth_bias = 6;
        data->scale_y = scale;
        data->scale_x = scale;
        (*(s8 *)((u8 *)node + 0x20)) = 0x70;
        part->unk_01 = 0x10;
        part->unk_02 = 0x10;
        data->color.c.b = 0;
        data->color.c.g = 0;
        data->color.c.r = 0;
        data->angle_z = rand() & 0xFFF;
        (*(Copy12 *)((u8 *)node + 0x48)) = (*(Copy12 *)((u8 *)D_8017520C + 0));
        data->source = (u8 *)node + 0x48;
    }
}
