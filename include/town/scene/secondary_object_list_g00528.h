#ifndef TOWN_SCENE_SECONDARY_OBJECT_LIST_G00528_H
#define TOWN_SCENE_SECONDARY_OBJECT_LIST_G00528_H
/* Secondary object list shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80092594. */

#include "common.h"
#include "m2c_compat.h"
#include "town/scene/active_object_overlap_g00529.h"

extern TownMotionListNode town_motion_list;

/* Functions defined in this translation unit. */
void append_secondary_list_node(TownMotionListNode *node);
void prepend_secondary_list_node(TownMotionListNode *node);

void init_secondary_list_record(TownMotionListNode *record, ObjectPosition *position, Box *bounds);
void update_record_overlap_node(TownMotionListNode *record);
s32 has_attached_state_type_1_or_3(TownMotionListNode *record);

#endif
