/* Active object overlap (G00529).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009263C.
 */
#include "town/scene/active_object_overlap_g00529.h"
#include "town/scene.h"

/*
 * Adds each box origin to its supplied offset and returns one only when all three inclusive
 * intervals overlap; touching faces count as overlap.
 */
s32 handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(Box *box_a, ObjectPosition *offset_a, Box *box_b, ObjectPosition *offset_b)
{
    s32 axis_a;
    s32 axis_b;

    if ((axis_a = offset_a->x.v + box_a->x, axis_b = offset_b->x.v + box_b->x, axis_b + box_b->w >= axis_a)
        && axis_a + box_a->w >= axis_b &&
        (axis_a = offset_a->y.v + box_a->y, axis_b = offset_b->y.v + box_b->y, axis_b + box_b->h >= axis_a)
            && axis_a + box_a->h >= axis_b &&
        (axis_a = offset_a->z.v + box_a->z, axis_b = offset_b->z.v + box_b->z, axis_b + box_b->d >= axis_a)
            && axis_a + box_a->d >= axis_b) {
        return 1;
    }
    return 0;
}

/* Checks whether the low 12-bit values differ by at most 511. */
s32 low_12_values_within_511(s32 value_a, s32 value_b) {
    return (u32) (((value_a & 0xFFF) - (value_b & 0xFFF)) + 0x1FF) < 0x3FFU;
}

/*
 * Searches the circular list for the first active node whose offset box overlaps the origin,
 * requiring a low-12-bit angle match within 511 for node types two and three.
 */
Node *handle_finds_first_eligible_active_node_in_circular_list(Node *origin) {
    Box *node_field_c;
    ObjectPosition *node_field_8;
    ObjectPosition *origin_field_8;
    Box *origin_field_c;
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
