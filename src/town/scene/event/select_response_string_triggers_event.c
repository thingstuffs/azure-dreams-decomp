#include "script_symbols.h"
#include "common.h"

extern char scene_string_fallback[];
extern char D_8001BCB4[];
extern char event_string_fallback[];
extern char D_80021484[];

extern char *award_next_unearned_milestone(s32, s32, s32, s32);
extern void func_8001A554(s32);

/* Selects a response string and triggers the event for selector 18. */
char *select_response_string_triggers_event(s32 unused, s32 passthru_1, s32 selector_id, s32 passthru_3)
{
    s32 arg2_val;
    u32 case_index;

    case_index = selector_id - 12;
    arg2_val = selector_id;
    switch (case_index) {
    case 7:
        return D_8001BCB4;
    case 6:
        func_8001A554(F_sbs32_pad09);
        return D_80021484;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector_id, passthru_1, arg2_val, passthru_3);
    case 0:
        return event_string_fallback;
    default:
        return scene_string_fallback;
    }
}
