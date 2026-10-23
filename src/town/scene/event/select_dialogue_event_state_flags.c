#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"

extern char scene_string_fallback[];
extern char D_8001BFF8[];
extern char event_string_fallback[];
extern char D_8001C8AF[];
extern char D_8001C8DC[];
extern char D_80021F90[];
extern char D_8002242C[];
extern char D_800224EE[];
extern char D_800225DB[];
extern char D_800225F5[];
extern char D_8002264A[];

extern char *award_next_unearned_milestone(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);
extern void func_8001A5CC(s32);

/* Select dialogue from event state and update flags for the selected interaction. */
char *select_dialogue_event_state_flags(s32 unused_0, s32 unused_1, s32 dialogue_id)
{
    s32 dialogue_selector = dialogue_id;

    switch (dialogue_selector - 12) {
    case 7:
        if (func_8001A64C(F_sbs32_pad14) == 0) {
            return D_8001BFF8;
        }
        return D_800225F5;
    case 6:
        if (func_8001A64C(F_sbs32_pad14) == 0) {
            func_8001A554(F_sbs32_pad13);
            func_8001A554(F_sbs32_pad14);
            func_8001A554(F_sbs32_pad35);
            func_8001A5CC(F_sbs32_pad34);
            return D_80021F90;
        }
        return D_800225DB;
    case 0:
        if (func_8001A64C(F_sbs32_pad14) == 0) {
            if (func_8001A64C(F_sbs32_pad11) != 0) {
                return D_8001C8AF;
            }
            if (func_8001A64C(F_sbs32_pad12) != 0) {
                return D_8001C8DC;
            }
            return event_string_fallback;
        }
        if (func_8001A64C(F_sbs32_pad35) != 0) {
            func_8001A5CC(F_sbs32_pad35);
            func_8001A554(F_sbs32_pad34);
            {
                u8 *globals_base = (u8 *)0x80010000;
                (*(void (**)(s32))((u8 *)*(void **)((u8 *)*(void **)(globals_base + 0x6000) + 0x20) + 0x258))(1);
                if (*(s32 *)((u8 *)*(void **)((u8 *)*(void **)(globals_base + 0x6000) + 0x1C) + 8) < 0x460) {
                    return D_800224EE;
                }
                return D_8002242C;
            }
        }
        return D_8002264A;
    case 40:
    case 41:
    case 42:
        return award_next_unearned_milestone(dialogue_selector);
    default:
        return scene_string_fallback;
    }
}
