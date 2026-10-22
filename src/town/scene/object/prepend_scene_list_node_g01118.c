/* prepend scene list node g01118
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01118 - CL:town/func_80091840.
 */
#include "town/scene/object/prepend_scene_list_node_g01118.h"

/* Insert a nonnull node immediately after the list head. */
s32 prepend_scene_list_node(Node *node) {
    extern Node D_800CFCB4[];
    u32 page = 0x800D0000;

    if (node != NULL) {
        Node *head;
        head = D_800CFCB4;
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        return 1;
    }
    return 0;
}

/* Insert a non-null node before the global list sentinel. */
s32 append_scene_list_node(Node *node) {
    extern u8 D_800CFCB4[];
    Node *head;

    if (node != NULL) {
        head = ((List *)D_800CFCB4)->head;
        node->next = (Node *)D_800CFCB4;
        node->prev = head;
        ((List *)D_800CFCB4)->head->next = node;
        ((List *)D_800CFCB4)->head = node;
        return 1;
    }
    return 0;
}

/* Insert a record and initialize its two values and status flags. */
void handle_insert_initialize_two_values_status_flags(Rec_D_800CFCB4 *node, s32 value_08, s32 value_0c) {
    if (prepend_scene_list_node(node) != 0) {
        node->unk_08 = value_08;
        node->unk_0C = value_0c;
        node->unk_15 = 1;
        node->unk_14 = 0;
    }
}
