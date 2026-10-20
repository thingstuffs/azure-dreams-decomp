#include "common.h"

typedef struct Node {
    u8 pad0[4];
    struct Node *next;
    s32 field8;
    s32 fieldC;
    u8 pad10[4];
    u8 type;
    u8 active;
    s16 angle;
} Node;

extern s32 handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes();
extern s32 low_12_values_within_511();

/* Finds the first eligible active node in the circular list. */
Node *handle_finds_first_eligible_active_node_in_circular_list(Node *origin) {
    s32 node_field_c;
    s32 node_field_8;
    s32 origin_field_8;
    s32 origin_field_c;
    Node *node;

    node = origin->next;
    origin_field_c = origin->fieldC;
    origin_field_8 = origin->field8;
    if (node != origin) {
        do {
            node_field_8 = node->field8;
            node_field_c = node->fieldC;
            if (node->active != 0) {
                if (((u32)(node->type - 2) >= 2U) ||
                    (low_12_values_within_511(node->angle, origin->angle) != 0)) {
                    if (handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(origin_field_c, origin_field_8, node_field_c, node_field_8) != 0) {
                        return node;
                    }
                }
            }
            node = node->next;
            if (node == origin) {
                break;
            }
        } while (1);
    }
    return 0;
}
