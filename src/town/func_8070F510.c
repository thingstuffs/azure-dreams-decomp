#include "common.h"

extern u8 D_8001B14C[];
extern u8 D_8001C6D0[];
extern u8 D_800227FB[];
extern u8 D_8001C018[];
extern void *award_next_unearned_milestone(s32);

/* Returns the data pointer selected by the given selector. */
void *func_80018510(s32 unused_0, s32 unused_1, s32 selector)
{
    switch (selector - 6) {
    case 0:
    case 6:
        return D_8001C6D0;
    case 13:
        return D_8001C018;
    case 12:
        return D_800227FB;
    case 46:
    case 47:
    case 48:
        return award_next_unearned_milestone(selector);
    default:
        return D_8001B14C;
    }
}
