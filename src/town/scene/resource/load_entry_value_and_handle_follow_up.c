#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "shared/record_ptrs.h"

typedef void (*TownCallback)(s32, s32, s32, s32);


extern char scene_string_fallback[];
extern char D_8001B9E0[];
extern char D_80020E44[];
extern char event_string_fallback[];

extern char *select_address_based_input(long long);


extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern s32 func_80019880(s32, s32);

/* Selects town text and runs the selected handler's fallback actions. */
char *load_entry_value_and_handle_follow_up(long long lookup, s32 text_selector)
{

    switch (text_selector - 12) {
    case 7:
    {
        char *text = select_address_based_input(lookup);
        scene_event_results[0] = text;
        if (text != 0) {
            return text;
        }
        return D_8001B9E0;
    }
    case 6:
    {
        char *text = get_local_global_table();
        scene_event_results[0] = text;
        if (text != 0) {
            return text;
        }
        func_8001A554(F_sbs32_pad25);
        if (func_8001A64C(F_sbs32_pad23) != 0 && func_80019880(13, 6) == 0) {
            (*(TownCallback *)((u8 *)((void **)*(void **)((void * *)(&town_scene_root)))[8] + 0x220))
            (6, 13, 0, 0);
        }
        return D_80020E44;
    }
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(text_selector);
    case 0:
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
