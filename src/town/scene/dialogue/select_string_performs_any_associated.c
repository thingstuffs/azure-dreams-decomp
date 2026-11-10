#include "slus/data.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "town/scene/dialogue.h"
#include "town/player/state.h"

extern char D_8001BA48[];
extern char event_string_fallback[];
extern char D_800213D4[];

/*
 * Returns selector-specific dialogue for IDs 12, 18, and 19, processes F_sbs32_pad08 for ID 19,
 * and delegates IDs 52 through 54 to milestone awards. Uses scene_string_fallback for other IDs.
 */
char *select_string_performs_any_associated(s32 unused_0, s32 unused_1, s32 selector)
{

    switch (selector - 12) {
    case 7:
        set_script_flag_bit(F_sbs32_pad08);
        return D_8001BA48;
    case 6:
        return D_800213D4;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector);
    case 0:
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
