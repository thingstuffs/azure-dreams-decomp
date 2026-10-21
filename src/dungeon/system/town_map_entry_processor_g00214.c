/* Town map entry processor (G00214). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/bank_d0a0:800CFCA8. */
#include "dungeon/system/town_map_entry_processor_g00214.h"

void advance_index_and_mark_completion(void *counterPtr) {
    s32 nextCounter;

    process_indexed_entry_record(*(s32 *)counterPtr);
    nextCounter = *(s32 *)counterPtr + 1;
    *(s32 *)counterPtr = nextCounter;
    if (nextCounter >= 0x80) {
        ((u16 *)counterPtr)[-1] |= 0x8000;
        D_800CFCA8 = 0;
        object_flag_block.flags |= 0x8000;
    }
}

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
