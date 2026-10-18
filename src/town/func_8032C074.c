#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001B910[];
extern u8 D_8001C354[];

/* Return the dispatch result for the fixed data tables and first and third arguments. */
s32 get_dispatch_result_fixed_data(s32 dispatch_value, s32 unused, s32 dispatch_option)
{
    return apply_entry_position(D_8001B910, D_8001C354, dispatch_value, dispatch_option);
}
