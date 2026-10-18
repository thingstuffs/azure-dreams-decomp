#include "modules/main_server_ship.h"
#include "common.h"






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
        if (*(s32 *)((s8 *)&(*(s32 (*)[])(&D_80028538)) + slot * 4) == state) {
            *(s32 *)((s8 *)&(*(s32 (*)[])(&D_80028530)) + slot * 4) += 1;
            slot_offset = slot * 4;
        } else {
            *(s32 *)((s8 *)&(*(s32 (*)[])(&D_80028530)) + slot * 4) = 0;
            slot_offset = slot * 4;
        }
        *(s32 *)((s8 *)&(*(s32 (*)[])(&D_80028538)) + slot * 4) = state;
        switch (state) {
        case 1:
        case 2:
            (*(s32 (*)[])(&D_800287D0))[slot] = state;
            card_boot_select_channel_mode(slot, (s32 *)slot_offset);
            return state;
        case 3:
            repeat_counts = (*(s32 (*)[])(&D_80028530));
            count_offset = slot * 4;
            break;
        case 4:
        case 5:
            (*(s32 (*)[])(&D_80084118))[slot] = 0;
            count_offset = slot * 4;
            repeat_counts = (*(s32 (*)[])(&D_80028530));
            break;
        default:
            card_boot_select_channel_mode(slot, (s32 *)slot_offset);
            return state;
        }
        if (*(s32 *)(count_offset + (s32)repeat_counts) >= 0xB) {
            *(s32 *)((s8 *)&(*(s32 (*)[])(&D_800287D0)) + count_offset) = state;
            *(s32 *)(count_offset + (s32)repeat_counts) = 0;
            *(s32 *)((s8 *)&(*(s32 (*)[])(&D_80028538)) + count_offset) = 0;
        }
        card_boot_select_channel_mode(slot, (s32 *)(count_offset + (s32)repeat_counts));
    }
    return state;
}
