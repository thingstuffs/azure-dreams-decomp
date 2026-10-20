#include "shared/object_node.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Node {
    u8 pad0[0x10];
    void (*cb)(void);
    u8 pad14[0xC];
    s32 field_0x20;
} Node;

extern void advance_index_and_mark_completion(void);
extern void *D_800CFCA8;

/* Allocates a node, initializes its callback and field, and saves the field pointer. */
void create_town_map_entry_processor(void) {
    Node *node = func_8003FC64(0);
    if (node != NULL) {
        node->cb = advance_index_and_mark_completion;
        node->field_0x20 = 0;
        node = (Node *)((u8 *)node + 0x20);
        D_800CFCA8 = node;
    }
}
