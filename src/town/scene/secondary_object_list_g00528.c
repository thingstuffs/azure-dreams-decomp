/* Secondary object list (G00528).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80092594.
 */
#include "town/scene/secondary_object_list_g00528.h"

/* Inserts a node before the doubly linked list sentinel D_800FE490. */
void append_secondary_list_node(void *node) {
    *(void **)node = D_800FE490;
    *((void **)node + 1) = *((void **)D_800FE490 + 1);
    *((void **)*((void **)D_800FE490 + 1)) = node;
    *((void **)D_800FE490 + 1) = node;
}

/* Inserts a node at the front of the doubly linked list. */
void prepend_secondary_list_node(void *node) {
    *(void **)node = D_800FE490[0];
    *((void **)node + 1) = D_800FE490;
    *((void **)D_800FE490[0] + 1) = node;
    D_800FE490[0] = node;
}

/* Initialize the record, store its two values, and set its state flags. */
void initialize_the_store_two_values_set_state_flags(Rec_D_800FE490 *record, s32 value_08, s32 value_0c) {
    append_secondary_list_node(record);
    record->unk_08 = value_08;
    record->unk_0C = value_0c;
    record->unk_15 = 1;
    record->unk_14 = 0;
}
