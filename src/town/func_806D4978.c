#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern void *townGetSpecialDataForLowValueId(s32);
extern void *func_80017960(void *, void *, s32, s32);
extern u8 D_800189EC[], D_80018B98[];

void func_80016978(s32 request, s32 unused, s32 selector)
{
    if (townGetSpecialDataForLowValueId(selector) == 0) func_80017960(D_800189EC, D_80018B98, request, selector);
}
