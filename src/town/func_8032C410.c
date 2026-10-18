#include "common.h"

extern s32 apply_entry_position(void *, void *, s32, s32);
extern u8 D_8001BA24[];
extern u8 D_8001C354[];

/* Process the request using D_8001BA24 and D_8001C354. */
s32 process_request_with_table_ba_24(s32 request, s32 unused, s32 context)
{
    return apply_entry_position(D_8001BA24, D_8001C354, request, context);
}
