#include "script_symbols.h"
#include "common.h"
#include "town/scene/milestone_rewards.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "town/player/state.h"

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

/* Select dialogue from event state and update flags for the selected interaction. */
char *select_dialogue_event_state_flags(void *unused_0, s32 unused_1, s32 dialogue_id)
{
    s32 dialogue_selector = dialogue_id;

    switch (dialogue_selector - 12) {
    case 7:
        if (get_script_flag_mask(F_sbs32_pad14) == 0) {
            return D_8001BFF8;
        }
        return D_800225F5;
    case 6:
        if (get_script_flag_mask(F_sbs32_pad14) == 0) {
            set_script_flag_bit(F_sbs32_pad13);
            set_script_flag_bit(F_sbs32_pad14);
            set_script_flag_bit(F_sbs32_pad35);
            clear_script_flag_bit(F_sbs32_pad34);
            return D_80021F90;
        }
        return D_800225DB;
    case 0:
        if (get_script_flag_mask(F_sbs32_pad14) == 0) {
            if (get_script_flag_mask(F_sbs32_pad11) != 0) {
                return D_8001C8AF;
            }
            if (get_script_flag_mask(F_sbs32_pad12) != 0) {
                return D_8001C8DC;
            }
            return event_string_fallback;
        }
        if (get_script_flag_mask(F_sbs32_pad35) != 0) {
            clear_script_flag_bit(F_sbs32_pad35);
            set_script_flag_bit(F_sbs32_pad34);
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
