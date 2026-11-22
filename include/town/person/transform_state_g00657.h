#ifndef TOWN_PERSON_TRANSFORM_STATE_G00657_H
#define TOWN_PERSON_TRANSFORM_STATE_G00657_H
/* Transform state. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C520C. */

#include "common.h"
#include "slus/town_map_selection_data.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"
#include "town/scene/list_setup.h"
#include "shared/town_object.h"

#include "town/scene/active_object_overlap_g00529.h"

extern Box D_800D4FB8[];
extern void D_800C2A10(void *object);
extern s16 D_800FE4A6;

/* Functions defined in this translation unit. */
Box *get_transform_entry_by_index(s32 entry_index);
void update_transform_motion_page(TownObjectRecord *object_data, ObjectPosition *motion);
void update_transform_state_value(TownObjectRecord *object);

#endif
