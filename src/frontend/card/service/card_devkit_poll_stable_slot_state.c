#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card.h"

/* Tracks repeated states and updates the selected slot after state-specific delays. */
s32 card_devkit_poll_stable_slot_state(void)
{
    s32 state;
    s32 slot_index;
    s32 state_case;

    state = card_devkit_dispatch_polled_event();
    slot_index = card_dev_has_selected_channel();
    if (state != 0) {
        if (card_last_polled_slot_state[slot_index] == state) {
            card_slot_state_repeat_count[slot_index]++;
        } else {
            card_slot_state_repeat_count[slot_index] = 0;
        }
        card_last_polled_slot_state[slot_index] = state;
        state_case = state - 1;
        switch (state_case) {
        case 0:
        case 1:
            card_stable_slot_state[slot_index] = state;
            break;
        case 2:
            if (card_slot_state_repeat_count[slot_index] >= 4) {
                card_stable_slot_state[slot_index] = state;
            }
            break;
        case 4:
        case 3:
            if (card_slot_state_repeat_count[slot_index] >= 11) {
                card_stable_slot_state[slot_index] = state;
            }
            break;
        default:
            break;
        }
        set_card_selection_state(slot_index);
    }
    return state;
}
