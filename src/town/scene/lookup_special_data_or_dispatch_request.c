#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"
extern void *func_80017960(void *, void *, s32, s32);
extern u8 D_800189EC[], D_80018B98[];

/*
 * Calls func_80017960 with the two local tables, request, and selector only when the selector has
 * no special data.
 */
void lookup_special_data_or_dispatch_request(s32 request, s32 unused, s32 selector)
{
    if (get_special_data_for_low_value_id(selector) == 0) func_80017960(D_800189EC, D_80018B98, request, selector);
}
