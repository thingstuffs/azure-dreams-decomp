#include "slus/data.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "town/scene.h"

extern char D_800227FB[];
extern char scene_choice_text[];




/* Returns the data pointer for the given selector and lookup ID. */
char *select_scene_text_or_flag_response(long long lookup_id, s32 data_selector)
{
    switch (data_selector - 12) {
    case 0:
        return select_response_selector_status_flags(lookup_id, data_selector);
    case 7:
        return scene_choice_text;
    case 6:
        return D_800227FB;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(data_selector);
    default:
        return scene_string_fallback;
    }
}
