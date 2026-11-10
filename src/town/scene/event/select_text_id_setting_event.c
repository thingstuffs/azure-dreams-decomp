#include "slus/data.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "town/scene/event.h"
#include "town/player/state.h"

extern char scene_choice_text[];
extern char D_8001D000[];
extern char D_800227FB[];

/* Selects text by ID, setting event 0x948 for selector 12. */
char *select_text_id_setting_event(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
{
    s32 saved_selector;
    u32 case_index;

    case_index = selector_id - 12;
    saved_selector = selector_id;
    switch (case_index) {
    case 7:
        return scene_choice_text;
    case 6:
        return D_800227FB;
    case 0:
        if (get_script_flag_mask(F_sbs32_pad30) == 0) {
            set_script_flag_bit(F_sbs32_pad30);
        }
        return D_8001D000;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector_id);
    default:
        return scene_string_fallback;
    }
}
