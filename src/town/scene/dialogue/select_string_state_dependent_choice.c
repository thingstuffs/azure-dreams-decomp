#include "script_symbols.h"
#include "common.h"

extern char scene_string_fallback[];
extern char scene_choice_text[];
extern char D_8001D6B5[];
extern char D_8001D7A5[];
extern char D_800227FB[];

extern char *award_next_unearned_milestone(s32);
extern s32 func_8001A64C(u32);

/*
 * Selects dialogue for IDs 18/19 and milestone awards for IDs 52 through 54; ID 12 chooses between
 * D_8001D6B5 and D_8001D7A5 using F_sbs32_pad32, with scene_string_fallback for other IDs.
 */
char *select_string_state_dependent_choice(s32 unused_0, s32 unused_1, s32 text_id)
{
    s32 selector = text_id;

    switch (selector - 12) {
    case 7:
        return scene_choice_text;
    case 6:
        return D_800227FB;
    case 0:
        if (func_8001A64C(F_sbs32_pad32) != 0) {
            return D_8001D6B5;
        }
        return D_8001D7A5;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector);
    default:
        return scene_string_fallback;
    }
}
