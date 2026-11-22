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

extern Box *person_transform_defaults[6];

typedef struct TownMotionListNode {
    struct TownMotionListNode *prev;
    struct TownMotionListNode *next;
    ObjectPosition *position;
    Box *bounds;
    struct TownMotionListNode *overlap;
    u8 type;
    u8 active;
    s16 angle;
} TownMotionListNode;

/* Functions defined in this translation unit. */
s32 offset_boxes_overlap(Box *box_a, ObjectPosition *offset_a, Box *box_b, ObjectPosition *offset_b);
TownMotionListNode *find_overlapping_active_node(TownMotionListNode *origin);

#endif
