#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"






/* Track consecutive state samples for a slot and apply state updates. */
s32 card_boot_debounce_card_status_events(void) {
    s32 slot;
    s32 state;
    s32 count_offset;
    s32 slot_offset;
    s32 *repeat_counts;

    state = card_boot_dispatch_event_callbacks();
    slot = card_boot_has_selected_channel();
    if (state != 0) {
        if (*(s32 *)((s8 *)&(*(s32 (*)[])(&card_last_status)) + slot * 4) == state) {
            *(s32 *)((s8 *)&(*(s32 (*)[])(&card_status_repeats)) + slot * 4) += 1;
            slot_offset = slot * 4;
        } else {
            *(s32 *)((s8 *)&(*(s32 (*)[])(&card_status_repeats)) + slot * 4) = 0;
            slot_offset = slot * 4;
        }
        *(s32 *)((s8 *)&(*(s32 (*)[])(&card_last_status)) + slot * 4) = state;
        switch (state) {
        case 1:
        case 2:
            (*(s32 (*)[])(&card_filtered_status))[slot] = state;
            card_boot_select_channel_mode(slot, (s32 *)slot_offset);
            return state;
        case 3:
            repeat_counts = (*(s32 (*)[])(&card_status_repeats));
            count_offset = slot * 4;
            break;
        case 4:
        case 5:
            (*(s32 (*)[])(&card_slot_completion_flags))[slot] = 0;
            count_offset = slot * 4;
            repeat_counts = (*(s32 (*)[])(&card_status_repeats));
            break;
        default:
            card_boot_select_channel_mode(slot, (s32 *)slot_offset);
            return state;
        }
        if (*(s32 *)(count_offset + (long)repeat_counts) >= 0xB) {
            *(s32 *)((s8 *)&(*(s32 (*)[])(&card_filtered_status)) + count_offset) = state;
            *(s32 *)(count_offset + (long)repeat_counts) = 0;
            *(s32 *)((s8 *)&(*(s32 (*)[])(&card_last_status)) + count_offset) = 0;
        }
        card_boot_select_channel_mode(slot, (s32 *)(count_offset + (long)repeat_counts));
    }
    return state;
}
