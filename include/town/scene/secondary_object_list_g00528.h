#ifndef TOWN_SCENE_SECONDARY_OBJECT_LIST_G00528_H
#define TOWN_SCENE_SECONDARY_OBJECT_LIST_G00528_H
/* Secondary object list shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80092594. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800FE490.h"

extern void *town_motion_list[];

/* Functions defined in this translation unit. */
void append_secondary_list_node(void *node);
void prepend_secondary_list_node(void *node);

#endif
