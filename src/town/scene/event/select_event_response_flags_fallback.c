#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"


extern char scene_string_fallback[];
extern char D_8001B8CC[];
extern char D_8001B9E0[];
extern char D_800206CC[];
extern char event_string_fallback[];

extern void *select_address_based_input(s32, s32);


extern s32 func_8001A64C(s32);
extern void func_8001A554(s32);

/* Select event response data and set flags when using fallback responses. */
void *select_event_response_flags_fallback(s32 handler_arg_a, s32 handler_arg_b, s32 selector)
{
    void *response;

    switch (selector) {
    case 19:
        do {
            response = select_address_based_input(handler_arg_a, handler_arg_b);
        } while (0);
        scene_event_results[0] = response;
        if (response != 0) {
            return response;
        }
        if (func_8001A64C(F_sbs32_pad02) == 0) {
            func_8001A554(F_sbs32_pad02);
            return D_8001B8CC;
        }
        return D_8001B9E0;
    case 18:
        response = get_local_global_table();
        scene_event_results[0] = response;
        if (response != 0) {
            return response;
        }
        if (func_8001A64C(F_okami_talk_00) == 0) {
            func_8001A554(F_okami_talk_00);
        }
        func_8001A554(F_sbs32_pad25);
        return D_800206CC;
    case 52:
    case 53:
    case 54:
        return award_next_unearned_milestone(selector);
    case 12:
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
