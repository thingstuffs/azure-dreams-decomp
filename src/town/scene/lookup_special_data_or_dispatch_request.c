#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
#include "town/scene/motion.h"
extern u8 D_800189EC[], D_80018B98[];

/*
 * Calls func_80017960 with the two local tables, request, and selector only when the selector has
 * no special data.
 */
void lookup_special_data_or_dispatch_request(s32 request, s32 unused, s32 selector)
{
    if (get_special_data_for_low_value_id(selector) == 0) apply_entry_position(D_800189EC, D_80018B98, request, selector);
}
