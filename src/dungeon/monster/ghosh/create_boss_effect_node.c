#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"

typedef struct Node {
    u8 pad0[8];
    void *part8;
    void *partC;
    void *data10;
} Node;

extern void register_node(Node *, void *);
extern void select_record_entry_and_value(void *, void *, s32);

extern u8 D_80170A54[9];

/* Allocate and initialize an effect node with default parameters and data. */
void create_boss_effect_node(void)
{
    Node *node;
    s16 *node_params;
    s16 *effect;
    u32 *part_words;

    node = (Node *)allocate_flagged_object_node(0x212);
    if (node != 0) {
        node_params = (s16 *)((u8 *)node + 0x20);
        node_params[11] = 0x1E;
        node_params[12] = 0x1E;
        node->data10 = D_80170A54;
        register_node(node, project_sprite_chain);

        effect = node->partC;
        ((SpriteFrameState *)effect)->unk_06 = 0;
        part_words = (u32 *)node->part8;
        part_words[0] = ((u32)view_reference_entity.x.v);
        part_words[1] = ((u32)view_reference_entity.y.v);
        part_words[2] = ((u32)view_reference_entity.z.v);

        effect = (s16 *)node->partC;
        effect[15] = 0x1000;
        effect[14] = 0x1000;
        ((SpriteFrameState *)effect)->color.c.b = 0;
        ((SpriteFrameState *)effect)->color.c.g = 0;
        ((SpriteFrameState *)effect)->color.c.r = 0;
        effect[10] |= 0x80;
        select_record_entry_and_value(effect, effect_sprite_sources, 0);
    }
}

/* MECHANISM: Node * stays live in s0, inducing the retail 0x18 frame and sole
   s0 save; separate node_params/effect locals encode retail's disjoint v1/a0 lives.
   Exact sh/sb/lhu widths and the three-word global copy preserve body shape. */
