/* Start dispatch event.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01230 - CL:town/func_804688AC.
 */
#include "town/scene/event/start_dispatch_event_g01230.h"

/* Initializes the town event once, invokes its callback, and reports whether it ran. */
s32 start_dispatch_event(s32 init_arg) {
    s16 *event;
    void *town;
    TownCallback callback;
    s32 started;

    if (town_event_state->dispatchState == 0) {
        select_next_event_state();
        town_event_state->dispatchState++;
        started = 1;
        event = select_event_data_table(town_event_state->dispatchState, town_event_state->unk_05);
        town = ((S_8001975C_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_20;
        callback = (*(TownCallback *)((u8 *)town + 0x2F8));
        callback(event[0], event[1]);
    } else {
        started = 0;
    }
    return started;
}

/* Checks the active event and dispatches the 0x27/0x200 handler when matched. */
s32 dispatch_active_event_27(void) {
    TownEventArgumentPair16 *event;

    if ((u8) town_event_state->dispatchState < 2U) {
        event = select_event_data_table(town_event_state->dispatchState,
                              town_event_state->unk_05);
        if (event->unk_00 == 0x27) {
            if (event->unk_02 == 0x200) {
                D_80016000->unk_20->callback_2F8(0x27, 0x200);
            }
        }
        return 1;
    }
    return 0;
}

/* Returns whether the current record's unk_01 field is 2. */
s32 is_dispatch_state_two(void) {
    return town_event_state->dispatchState == 2;
}

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
