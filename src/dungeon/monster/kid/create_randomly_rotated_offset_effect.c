#include "shared/sprite_frame_state.h"
#include "dungeon/monster/kid.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "engine/node.h"
#include "sdk/libc.h"

typedef struct {
    u32 word[3];
} __attribute__((packed)) Copy12;

extern u8 D_8017520C[12];



/* Creates an effect at an offset from the source position with a random rotation. */
/* Creates a randomly rotated Kid sprite 40 units above the source, with the supplied scale and a copied
 * texture entry. */
void create_randomly_rotated_offset_effect(void *unused_ptr, ObjectPosition *source_pos, SpriteFrameState *unused_value, s16 scale)
{
    ObjectNodeHeader * node;
    RandomlyRotatedOffsetEffectBody *part;
    SpriteFrameState *data;
    ObjectPosition *pos;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        part = NODE_BODY(node);
        part->unk_1A.s = 65;
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
        part->unk_00.s = 0x70;
        part->unk_01.s = 0x10;
        part->unk_02.s = 0x10;
        data->color.c.b = 0;
        data->color.c.g = 0;
        data->color.c.r = 0;
        data->angle_z = rand() & 0xFFF;
        (*(Copy12 *)((u8 *)node + 0x48)) = (*(Copy12 *)(D_8017520C + 0));
        data->source = (u8 *)node + 0x48;
    }
}
