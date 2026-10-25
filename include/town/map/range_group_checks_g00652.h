#ifndef TOWN_MAP_RANGE_GROUP_CHECKS_G00652_H
#define TOWN_MAP_RANGE_GROUP_CHECKS_G00652_H
/* inferred-strong G00652: range_group_checks_g00652; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C4508. */

#include "common.h"
#include "m2c_compat.h"

extern s32 D_800D456C;
/* extern */
extern struct RuntimeState map_runtime_state;
extern s16 *D_800D4640[];
extern s16 *D_800D4658[];
extern s16 *D_800D4660[];

/* Functions defined in this translation unit. */
s32 find_containing_range_group(s32 value, s16 **range_groups);
s32 pass_value_and_range_groups(s32 value);
s32 check_masked_value_in_current_range(s32 value);

#endif
