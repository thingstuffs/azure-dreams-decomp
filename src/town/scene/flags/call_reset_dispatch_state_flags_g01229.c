/* Call reset dispatch state flags.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01229 - CL:town/func_804686A4.
 */
#include "town/scene/flags/call_reset_dispatch_state_flags_g01229.h"

/* Call reset_dispatch_state_and_flags, increment the byte at D_8001E950, and return zero. */
s32 call_reset_dispatch_state_flags(s32 first_value, s32 second_value) {
    reset_dispatch_state_and_flags();
    town_event_state->unk_00 += 1;
    return 0;
}

/* Shop tick: on an idle counter, run the 0x1E82C check and bump the pending count. */
u8 *tick_shop_event_state(void) {
    if (func_8001E670(sn_open_sekkyo_end) == 0) {
        return D_80018A30;
    }
    if (func_8001E82C() != 0) {
        reset_dispatch_state_and_flags();
    }
    town_event_state->unk_00 += 1;
    return (u8 *)0;
}

/* Town state query: when flag 0x1391 is clear or flag 0xA2 is set, return the table entry the object's 0x2D4 callback picks; otherwise run the fallback and bump its counter. */
s32 query_event_state_or_reset(void)
{
    s32 index;

    if ((func_8001E670(F_veld_kill) == 0) ||
        (func_8001E670(F_end_ending) != 0)) {
        index = (*(Callback **)((u8 *)*(void **)((u8 *)D_80016000 + 0x20) + 0x2D4))(0);
        return D_80018448[index];
    }

    reset_dispatch_state_and_flags();
    town_event_state->unk_00++;
    return 0;
}

/* Return the table value selected by the callback at offset 0x2D4. */
s32 get_callback_selected_table_value(void) {
    return *(s32 *)((s8 *) &D_800186A8 + (D_80016000->unk_20->callback_2D4(0) * 4));
}

/* Update script flags and dispatch opcodes until a handler returns a result. */
void run_event_opcode_script(s32 setup_arg0, s32 setup_arg1, s32 setup_arg2, s32 setup_arg3) {
    s32 opcode_result;
    u32 state_page_addr;
    u8 *state_page;
    EventOpcodeHandler *opcode_handlers;

    process_history_entries_by_mode();
    if (func_8001E670(F_end_ending_step0) != 0) {
        if (func_8001E670(F_guy_sword_pickup) == 0) {
            func_8001E578(F_sbs01_pad20);
        } else {
            func_8001E5F0(F_sbs01_pad20);
        }
        if (func_8001E670(F_ultima_egg_pickup) == 0) {
            if (((TownPairCallback *)((u8 *)((S_80019560_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_20 + 0x350))[0](1,
                0x12) != 0) {
                func_8001E578(F_ultima_egg_pickup);
                func_8001E5F0(F_sbs01_pad21);
                state_page_addr = 0x80020000;
            } else {
                func_8001E578(F_sbs01_pad21);
                state_page_addr = 0x80020000;
            }
        } else {
            func_8001E5F0(F_sbs01_pad21);
            state_page_addr = 0x80020000;
        }
    } else {
        func_8001E5F0(F_sbs01_pad20);
        func_8001E5F0(F_sbs01_pad21);
        state_page_addr = 0x80020000;
    }
    state_page = (u8 *)state_page_addr;
    opcode_handlers = D_800178E8;
    *(u8 **)(state_page - 0x16B0) = ((S_80019560_0 *)(*(void **)((s8 *)(&D_80016000))))->unk_40 + 8;
    do {
        state_page_addr = opcode_handlers[**(u8 **)(state_page - 0x16B0)]();
        opcode_result = state_page_addr;
    } while (opcode_result == 0);
    D_8001E95C[0] = opcode_result;
    if (func_8001E670(D_800178BA[0]) == 0) {
        reset_dispatch_state_and_flags();
    }
}

/* Clear two state bytes and process five fixed identifiers. */
void reset_dispatch_state_and_flags(void) {
    town_event_state->dispatchState = 0;
    town_event_state->unk_06 = 0;
    func_8001E5F0(F_sbs01_pad11);
    func_8001E5F0(F_sbs01_pad12);
    func_8001E5F0(F_sbs01_pad13);
    func_8001E5F0(Ft_home01_rees_once);
    func_8001E5F0(F_tw_rain_del);
}
