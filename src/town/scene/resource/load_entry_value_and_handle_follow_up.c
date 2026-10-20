#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*TownCallback)(s32, s32, s32, s32);

extern void *D_8001B16C[4];
extern char D_8001B14C[];
extern char D_8001B9E0[];
extern char D_80020E44[];
extern char D_8001C6D0[];

extern char *select_address_based_input(long long);
extern char *get_local_global_table(void);
extern char *award_next_unearned_milestone(s32);
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
        D_8001B16C[0] = text;
        if (text != 0) {
            return text;
        }
        return D_8001B9E0;
    }
    case 6:
    {
        char *text = get_local_global_table();
        D_8001B16C[0] = text;
        if (text != 0) {
            return text;
        }
        func_8001A554(F_sbs32_pad25);
        if (func_8001A64C(F_sbs32_pad23) != 0 && func_80019880(13, 6) == 0) {
            (*(TownCallback *)((u8 *)((void **)*(void **)((void * *)(&D_80016000)))[8] + 0x220))
            (6, 13, 0, 0);
        }
        return D_80020E44;
    }
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(text_selector);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
