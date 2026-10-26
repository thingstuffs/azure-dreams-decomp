#include "common.h"
#include "engine/scene.h"
#include "slus.h"
#include "shared/object_node.h"

typedef struct S_801EAFE8
{
    struct S_801EAFE8 *next;
    u8 pad[0x124 - 4];
}
S_801EAFE8;

extern S_801EAFE8 D_801EAFE8[0x100];


extern void * free_node_list_head;


extern void * active_node_list_head;

/* Initialize the node pool free list and reset the pointer tables. */
void runtime_reset_object_pool(void)
{
    s32 index;
    S_801EAFE8 *free_node;
    S_801EAFE8 *clear_node;
    ObjectNodeHeader **slots_a_base;
    void **slots_b_base;
    ObjectNodeHeader **slot_a;
    void **slot_b;

    free_node = D_801EAFE8;

    for (index = 0, clear_node = free_node; index < 0x100; index++) {
        zero_words((s32 *)clear_node, 0x49);
        clear_node = (S_801EAFE8 *)(((u8 *)clear_node) + 0x124);
    }

    for (index = 0xFE; index >= 0; index--) {
        free_node->next = (S_801EAFE8 *)(((u8 *)free_node) + 0x124);
        free_node = free_node->next;
    }

    index = 0x1F;
    slots_a_base = registered_draw_objects;
    slot_a = slots_a_base + 0x1F;
    slots_b_base = registered_draw_callbacks;
    slot_b = slots_b_base + 0x1F;
    free_node->next = 0;
    active_node_list_head = 0;
    free_node_list_head = D_801EAFE8;

    for (; index >= 0; index--) {
        *slot_b = 0;
        *slot_a = 0;
        slot_a--;
        slot_b--;
    }
}
