/* prepend scene list node g01118
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01118 - CL:town/func_80091840.
 */
#include "town/scene/object/prepend_scene_list_node_g01118.h"

/* Insert a nonnull node immediately after the list head. */
s32 prepend_scene_list_node(TownSceneListNode *node) {
    u32 page = 0x800D0000;

    if (node != NULL) {
        TownSceneListNode *head;
        head = town_actor_control;
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        return 1;
    }
    return 0;
}

/* Insert a non-null node before the global list sentinel. */
s32 append_scene_list_node(TownSceneListNode *node) {
    TownSceneListNode *head;

    if (node != NULL) {
        head = town_actor_control->prev;
        node->next = town_actor_control;
        node->prev = head;
        town_actor_control->prev->next = node;
        town_actor_control->prev = node;
        return 1;
    }
    return 0;
}

/*
 * On successful scene-list insertion, stores the two supplied values, marks byte 0x15 present, and
 * clears mode byte 0x14.
 */
void handle_insert_initialize_two_values_status_flags(void *record, void *position, void *bounds) {
    TownSceneListNode *node = record;
    if (prepend_scene_list_node(node) != 0) {
        node->position = position;
        node->bounds = bounds;
        node->active = 1;
        node->mode = 0;
    }
}
