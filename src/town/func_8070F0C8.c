#include "common.h"

extern u8 D_800227FB[];
extern u8 D_8001B14C[];
extern u8 D_8001C018[];

extern u8 *award_next_unearned_milestone(u32);
extern u8 *select_response_selector_status_flags(s32);

/* Returns the data pointer for the given selector and lookup ID. */
u8 *get_pointer_selector_lookup_id(long long lookup_id, s32 data_selector)
{
    switch (data_selector - 12) {
    case 0:
        return select_response_selector_status_flags((s32)lookup_id);
    case 7:
        return D_8001C018;
    case 6:
        return D_800227FB;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(data_selector);
    default:
        return D_8001B14C;
    }
}
