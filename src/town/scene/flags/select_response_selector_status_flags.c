#include "script_symbols.h"
#include "common.h"

extern char scene_string_fallback[];
extern char scene_choice_text[];
extern char event_string_fallback[];
extern char D_8001D000[];
extern char D_8001D3CC[];
extern char D_80022694[];

extern s32 town_table_contains_first_byte(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern char *award_next_unearned_milestone(s32, s32, s32, s32);

/* Selects a response from the selector and status flags, updating flags for special cases. */
char *select_response_selector_status_flags(s32 unused, s32 value, s32 selection, s32 extra)
{
    s32 selector = selection;
    s32 arg2_val;
    u32 table_index;

    table_index = selector - 12;
    arg2_val = selector;
    switch (table_index) {
    case 7:
        return scene_choice_text;
    case 6:
        return D_80022694;
    case 0:
        if (town_table_contains_first_byte(6) != 0) {
            func_8001A554(F_sbs32_pad16);
        }
        if (town_table_contains_first_byte(0xB) != 0) {
            func_8001A554(F_sbs32_pad17);
        }
        if (func_8001A64C(F_sbs32_pad16) == 0) {
            if (func_8001A64C(F_sbs32_pad17) == 0) {
                if (func_8001A64C(F_sbs32_pad30) == 0) {
                    func_8001A554(F_sbs32_pad30);
                    return D_8001D000;
                }
                {
                    s32 flag_94a_set = func_8001A64C(F_sbs32_pad32);
                    if (flag_94a_set == 0) {
                        func_8001A554(F_sbs32_pad32);
                        func_8001A554(F_casino_build);
                        return D_8001D3CC;
                    }
                }
                func_8001A554(F_sbs32_pad30);
                return D_8001D000;
            }
        }
        if (func_8001A64C(F_sbs32_pad16) != 0) {
            if (func_8001A64C(F_sbs32_pad17) == 0) {
                func_8001A554(F_sbs32_pad32);
                func_8001A554(F_casino_build);
                return D_8001D3CC;
            }
        }
        if (func_8001A64C(F_sbs32_pad16) == 0) {
            if (func_8001A64C(F_sbs32_pad17) != 0) {
                func_8001A554(F_sbs32_pad30);
                return D_8001D000;
            }
        }
        if (func_8001A64C(F_sbs32_pad16) != 0) {
            if (func_8001A64C(F_sbs32_pad17) != 0) {
                func_8001A554(F_sbs32_pad32);
                func_8001A554(F_casino_build);
                return D_8001D3CC;
            }
        }
        return event_string_fallback;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector, value, arg2_val, extra);
    default:
        return scene_string_fallback;
    }
}
