#include "common.h"
#include "town/scene/milestone_rewards.h"

extern char scene_string_fallback[];
extern char D_8001B9E8[];
extern char event_string_fallback[];
extern char D_80021386[];



/* Selects a text string, delegating selector 52 to the shared lookup. */
char *select_pointer_with_dispatch_cases(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
{
    s32 saved_selector;
    u32 case_index;

    case_index = selector_id - 12;
    saved_selector = selector_id;
    switch (case_index) {
    case 7:
        return D_8001B9E8;
    case 6:
        return D_80021386;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector_id);
    case 0:
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
