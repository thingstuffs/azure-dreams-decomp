#include "common.h"

extern u8 scene_string_fallback[];
extern u8 event_string_fallback[];
extern u8 D_800227FB[];
extern u8 scene_choice_text[];
extern void *award_next_unearned_milestone(s32);

/* Returns the data pointer selected by the given selector. */
void *select_data_for_selector(s32 unused_0, s32 unused_1, s32 selector)
{
    switch (selector - 6) {
    case 0:
    case 6:
        return event_string_fallback;
    case 13:
        return scene_choice_text;
    case 12:
        return D_800227FB;
    case 46:
    case 47:
    case 48:
        return award_next_unearned_milestone(selector);
    default:
        return scene_string_fallback;
    }
}
