#include "shared/object_node.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "slus.h"

typedef struct Node {
    u8 pad0[8];
    void *part8;
    void *partC;
    void *data10;
} Node;

/* Allocate and initialize an effect node with default parameters and data. */
void create_boss_effect_node(void)
{
    ObjectNodeHeader *node;
    s16 *node_params;
    s16 *effect;
    u32 *part_words;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        node_params = (s16 *)((u8 *)node + 0x20);
        node_params[11] = 0x1E;
        node_params[12] = 0x1E;
        node->update_callback = apply_boss_direction_table_state;
        register_node(node, project_sprite_chain);

        effect = node->sprite;
        ((SpriteFrameState *)effect)->depth_bias = 0;
        part_words = (u32 *)node->position;
        part_words[0] = ((u32)view_reference_entity.x.v);
        part_words[1] = ((u32)view_reference_entity.y.v);
        part_words[2] = ((u32)view_reference_entity.z.v);

        effect = (s16 *)node->sprite;
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
