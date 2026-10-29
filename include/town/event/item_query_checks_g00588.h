#ifndef TOWN_EVENT_ITEM_QUERY_CHECKS_G00588_H
#define TOWN_EVENT_ITEM_QUERY_CHECKS_G00588_H
/* inferred-strong G00588: item_query_checks_g00588; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC118, CL:town/func_800AC164, CL:town/func_800AC198, CL:town/func_800AC210, PD:town/engine:800D1054. */

#include "common.h"
#include "m2c_compat.h"
#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
#include "script_symbols.h"
#include "engine/object/test_resident_bitmap_bit_api.h"

extern s16 town_query_group_ids[];
extern s16 D_800D1064[];



/* Functions defined in this translation unit. */
s32 find_sentinel_table_value_index(s32 target_value);
s32 test_selected_resident_flag(s32 table_index);
s32 get_query_result_for_check_type(s32 check_type);
s32 check_slot_threshold_or_fallback(s32 slot);

#endif
