#include "shared/object_node.h"
#include "common.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/scene.h"
#include "slus.h"

/* Node returned by func_8003FC64. We only model the fields touched here:
 * a "public" area starting at offset 0x20 (owner back-pointer), and two
 * writes made through a pointer into that area: +4 (the stashed a1 arg)
 * and -0x10 (a callback function pointer at absolute offset 0x10). */
typedef struct S_8004EDA8_node {
    u8 pad_0x0[0x20];
    void *owner_0x20;   /* 0x20: back-pointer to a0 */
    void *arg_0x24;      /* 0x24: stashed a1 */
} S_8004EDA8_node;

/* The object passed in as a0: only its 0x1E halfword (flags) is touched
 * here, matching the field used across the func_8003FC64 family. */

/* Clears the owner flag and allocates and initializes a callback node with its context. */
void *scene_create_resource_transition(void *owner_arg, void *context_arg)
{
    ObjectNodeHeader *owner = owner_arg;
    void *context = context_arg;
    S_8004EDA8_node *node;
    u8 *node_fields;

    owner->flags = owner->flags & 0xDFFF;
    node = allocate_flagged_object_node(0);
    if (node != 0) {
        node_fields = (u8 *)&node->owner_0x20;
        *(void **)(node_fields + 4) = context;
        node->owner_0x20 = owner;
        SD_Call(0xD1);
        ((ObjectNodeHeader *)(node_fields - 0x20))->update_callback = schedule_deferred_resource_transition;
        scene_begin_transition_texture_read((u8 *)node + 0x28);
    }
    return node;
}
