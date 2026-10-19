#include "common.h"
#include "shared/town_dispatch_object.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001BB5C[];

/* Dispatch through D_8001BB5C and D_8001C358 and return the result. */
s32 dispatch_through_table_bb_5_c(s32 dispatch_value, s32 unused, s32 dispatch_context)
{
    return apply_entry_position(D_8001BB5C, D_8001C358, dispatch_value, dispatch_context);
}
