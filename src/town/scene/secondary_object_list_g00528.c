/* Secondary object list.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80092594.
 */
#include "town/scene/secondary_object_list_g00528.h"
#include "town/scene.h"

/*
 * Inserts the node immediately before the town_motion_list sentinel and updates both neighboring
 * links.
 */
void append_secondary_list_node(TownMotionListNode *node) {
    node->prev = &town_motion_list;
    node->next = town_motion_list.next;
    town_motion_list.next->prev = node;
    town_motion_list.next = node;
}

/* Inserts a node at the front of the doubly linked list. */
void prepend_secondary_list_node(TownMotionListNode *node) {
    node->prev = town_motion_list.prev;
    node->next = &town_motion_list;
    town_motion_list.prev->next = node;
    town_motion_list.prev = node;
}

/*
 * Appends the record to the secondary list, stores the two supplied values, sets byte 0x15 to one,
 * and clears mode byte 0x14.
 */
void init_secondary_list_record(TownMotionListNode *record, ObjectPosition *position, Box *bounds) {
    append_secondary_list_node(record);
    record->position = position;
    record->bounds = bounds;
    record->active = 1;
    record->type = 0;
}
