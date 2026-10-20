#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern void *get_special_data_for_low_value_id(s32);
extern void *func_80017960(void *, void *, s32, s32);
extern u8 D_800189EC[], D_80018B98[];

void lookup_special_data_or_dispatch_request(s32 request, s32 unused, s32 selector)
{
    if (get_special_data_for_low_value_id(selector) == 0) func_80017960(D_800189EC, D_80018B98, request, selector);
}
