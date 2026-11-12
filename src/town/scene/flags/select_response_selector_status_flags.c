#include "slus/data.h"
#include "slus/event_string_fallback_data.h"
#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "town/scene/flags.h"
#include "town/player/state.h"
#include "town.h"

extern char scene_choice_text[];
extern char D_8001D000[];
extern char D_8001D3CC[];
extern char D_80022694[];

/* Selects a response from the selector and status flags, updating flags for special cases. */
char *select_response_selector_status_flags(long long unused, s32 selection)
{
    s32 selector = selection;
    s32 saved_selector;
    u32 table_index;

    table_index = selector - 12;
    saved_selector = selector;
    switch (table_index) {
    case 7:
        return scene_choice_text;
    case 6:
        return D_80022694;
    case 0:
        if (town_table_contains_first_byte_b(6) != 0) {
            set_script_flag_bit(F_sbs32_pad16);
        }
        if (town_table_contains_first_byte_b(0xB) != 0) {
            set_script_flag_bit(F_sbs32_pad17);
        }
        if (get_script_flag_mask(F_sbs32_pad16) == 0) {
            if (get_script_flag_mask(F_sbs32_pad17) == 0) {
                if (get_script_flag_mask(F_sbs32_pad30) == 0) {
                    set_script_flag_bit(F_sbs32_pad30);
                    return D_8001D000;
                }
                {
                    s32 flag_94a_set = get_script_flag_mask(F_sbs32_pad32);
                    if (flag_94a_set == 0) {
                        set_script_flag_bit(F_sbs32_pad32);
                        set_script_flag_bit(F_casino_build);
                        return D_8001D3CC;
                    }
                }
                set_script_flag_bit(F_sbs32_pad30);
                return D_8001D000;
            }
        }
        if (get_script_flag_mask(F_sbs32_pad16) != 0) {
            if (get_script_flag_mask(F_sbs32_pad17) == 0) {
                set_script_flag_bit(F_sbs32_pad32);
                set_script_flag_bit(F_casino_build);
                return D_8001D3CC;
            }
        }
        if (get_script_flag_mask(F_sbs32_pad16) == 0) {
            if (get_script_flag_mask(F_sbs32_pad17) != 0) {
                set_script_flag_bit(F_sbs32_pad30);
                return D_8001D000;
            }
        }
        if (get_script_flag_mask(F_sbs32_pad16) != 0) {
            if (get_script_flag_mask(F_sbs32_pad17) != 0) {
                set_script_flag_bit(F_sbs32_pad32);
                set_script_flag_bit(F_casino_build);
                return D_8001D3CC;
            }
        }
        return event_string_fallback;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector);
    default:
        return scene_string_fallback;
    }
}
