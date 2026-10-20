#include "common.h"

typedef struct S_801EAFE8
{
    struct S_801EAFE8 *next;
    u8 pad[0x124 - 4];
}
S_801EAFE8;

extern S_801EAFE8 D_801EAFE8[0x100];


extern void * free_node_list_head;


extern void * D_80081498;

typedef struct S_80044AAC S_80044AAC;

extern S_80044AAC *registered_draw_objects[0x20];
extern S_80044AAC *registered_draw_callbacks[0x20];
extern void zero_words(s32 *p, s32 n);

/* Initialize the node pool free list and reset the pointer tables. */
void runtime_reset_object_pool(void)
{
    s32 index;
    S_801EAFE8 *free_node;
    S_801EAFE8 *clear_node;
    S_80044AAC **slots_a_base;
    S_80044AAC **slots_b_base;
    S_80044AAC **slot_a;
    S_80044AAC **slot_b;

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
    D_80081498 = 0;
    free_node_list_head = D_801EAFE8;

    for (; index >= 0; index--) {
        *slot_b = 0;
        *slot_a = 0;
        slot_a--;
        slot_b--;
    }
}
