#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"


extern s32 func_8001E670(s32 id);
extern void func_8001E578(s32 id);
extern void func_8001E5F0(s32 id);
extern u8 find_first_enabled_entry_id(void);
extern s32 count_enabled_town_entries(void);
extern s32 find_first_enabled_paired_entry(void);
extern s32 advance_to_next_enabled_entry(void);

s32 select_next_event_state(void) {
    u8 value;
    s32 result;
    void *state;

    if ((func_8001E670(F_sero_end) != 0) && (func_8001E670(F_niko_selro_asa) == 0)) {
        func_8001E578(F_niko_selro_asa);
        func_8001E5F0(Fp_niko_kenkatyu);
        *((u8 *)town_event_state + 5) = 9;
        return;
    }
    if ((func_8001E670(F_s04_niko_step) != 0) && (func_8001E670(F_sbs01_pad18) == 0)) {
        func_8001E578(F_sbs01_pad18);
        *((u8 *)town_event_state + 5) = 10;
        return;
    }
    if (func_8001E670(F_end_ending) == 0) {
        if ((func_8001E670(F_veldil_dungeon_deatta) != 0) && (func_8001E670(F_sbs01_pad16) == 0)) {
            func_8001E578(F_sbs01_pad16);
            *((u8 *)town_event_state + 3) = find_first_enabled_entry_id();
        }
        if ((func_8001E670(F_sbs01_pad09) != 0) && (func_8001E670(sn_return_successful) == 0)) {
            state = town_event_state;
            value = *((u8 *)state + 3);
            if (value != 0) {
                *((u8 *)state + 4) = value;
                *((u8 *)town_event_state + 5) = 7;
            } else {
                *((u8 *)state + 5) = 8;
            }
            return;
        }
        if (func_8001E670(F_sbs01_pad09) != 0) {
            state = town_event_state;
            value = *((u8 *)state + 3);
            if (value != 0) {
                *((u8 *)state + 4) = value;
                *((u8 *)town_event_state + 5) = 5;
            } else {
                *((u8 *)state + 5) = 6;
            }
            return;
        }
        if ((func_8001E670(F_veldil_dungeon_deatta) != 0) && (func_8001E670(F_sbs01_pad09) == 0)) {
            func_8001E578(F_sbs01_pad09);
            state = town_event_state;
            value = *((u8 *)state + 3);
            if (value != 0) {
                *((u8 *)state + 4) = value;
                *((u8 *)town_event_state + 5) = 3;
            } else {
                *((u8 *)state + 5) = 4;
            }
            return;
        }
    }
    if (count_enabled_town_entries() != 0) {
        result = find_first_enabled_paired_entry();
        if (result == 0) {
            result = advance_to_next_enabled_entry();
        }
        *((u8 *)town_event_state + 4) = result;
        *((u8 *)town_event_state + 5) = 2;
        return;
    }
    if ((func_8001E670(F_selfy_get_tamago) == 0) || (func_8001E670(Ft_niko_love) != 0)) {
        *((s8 *)town_event_state + 5) = 0;
        return;
    }
    state = town_event_state;
    *((s8 *)state + 5) = 1;
}
