#include "script_symbols.h"
#include "common.h"

extern char D_8001B14C[];
extern char D_8001BF7C[];
extern char D_8001C6D0[];
extern char D_8001C8AF[];
extern char D_8001C8DC[];
extern char D_80021EE4[];

extern char *award_next_unearned_milestone(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);

/* Selects a string by selector and state flags. */
char *select_string_selector_state_flags(s32 unused_0, s32 unused_1, s32 string_selector)
{
    s32 selector = string_selector;

    switch (selector - 12) {
    case 7:
        return D_8001BF7C;
    case 6:
        return D_80021EE4;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(selector);
    case 0:
        func_8001A554(F_sbs32_pad25);
        if (func_8001A64C(F_sbs32_pad11) != 0) {
            return D_8001C8AF;
        }
        if (func_8001A64C(F_sbs32_pad12) != 0) {
            return D_8001C8DC;
        }
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
