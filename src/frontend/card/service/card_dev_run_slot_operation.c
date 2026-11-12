#include "frontend/card/save_slot.h"
#include "common.h"
#include "frontend/card/decimal_format.h"
#include "frontend/card/service.h"
#include "frontend/card/server_aliases.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card.h"

extern s32 func_8040153C(void);
extern void configure_target_for_active_state_and_entry(void *target, s32 entry_index);

extern CardSaveSlot card_slot_header_cache[];

/* Run the slot operation to completion and update its counters. */
s32 card_dev_run_slot_operation(s32 slot_index)
{
    u8 state[32];
    s32 count;
    s32 result;

    count = 0;
    configure_target_for_active_state_and_entry(state, slot_index);
    _card_wait_80408654(0);
    _card_wait_80408654(1);
    card_dev_drain_sw_events();
    func_8007CAE8(state);
    do {
        result = func_8040153C();
        if (result == 0) {
            count++;
            func_800702F0(0);
        }
    } while (result == 0);
    func_8007C040(card_decimal_format, card_counter_label, count);

    if (slot_index < 5) {
        s32 *counters;
        s32 *counter_dst;
        s32 *counter_src;
        s32 counter_selector;

        counters = D_8009EB58;
        counter_dst = counters;
        counter_selector = card_selected_channel;
        card_slot_header_cache[slot_index].words[0] = 0;
        if (counter_selector != 0) {
            counter_dst++;
        }
        counter_src = counters;
        if (counter_selector != 0) {
            counter_src++;
        }
        *counter_dst = *counter_src + 3;
    }
    return result == 1;
}
