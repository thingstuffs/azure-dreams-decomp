#ifndef TOWN_SCENE_ACTIVE_OBJECT_OVERLAP_G00529_H
#define TOWN_SCENE_ACTIVE_OBJECT_OVERLAP_G00529_H
/* Active object overlap shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009263C. */

#include "common.h"
#include "shared/entity.h"

typedef struct Box {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    s32 h;
    s32 d;
} Box;

typedef struct Node {
    u8 pad0[4];
    struct Node *next;
    ObjectPosition *field8;
    Box *fieldC;
    u8 pad10[4];
    u8 type;
    u8 active;
    s16 angle;
} Node;

/* Functions defined in this translation unit. */
s32 handle_tests_whether_two_offset_boxes_overlap_touch_all_three_axes(Box *box_a, ObjectPosition *offset_a, Box *box_b, ObjectPosition *offset_b);
s32 low_12_values_within_511(s32 value_a, s32 value_b);
Node *handle_finds_first_eligible_active_node_in_circular_list(Node *origin);

#endif
