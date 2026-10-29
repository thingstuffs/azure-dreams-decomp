/* Secondary object list (G00528).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80092594.
 */
#include "town/scene/secondary_object_list_g00528.h"
#include "town/scene.h"

/*
 * Inserts the node immediately before the town_motion_list sentinel and updates both neighboring
 * links.
 */
void append_secondary_list_node(void *node) {
    *(void **)node = town_motion_list;
    *((void **)node + 1) = *((void **)town_motion_list + 1);
    *((void **)*((void **)town_motion_list + 1)) = node;
    *((void **)town_motion_list + 1) = node;
}

/* Inserts a node at the front of the doubly linked list. */
void prepend_secondary_list_node(void *node) {
    *(void **)node = town_motion_list[0];
    *((void **)node + 1) = town_motion_list;
    *((void **)town_motion_list[0] + 1) = node;
    town_motion_list[0] = node;
}

/*
 * Appends the record to the secondary list, stores the two supplied values, sets byte 0x15 to one,
 * and clears mode byte 0x14.
 */
void initialize_the_store_two_values_set_state_flags(Rec_D_800FE490 *record, s32 value_08, s32 value_0c) {
    append_secondary_list_node(record);
    record->unk_08 = value_08;
    record->unk_0C = value_0c;
    record->unk_15 = 1;
    record->unk_14 = 0;
}
