#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"

extern s32 card_dev_has_selected_channel(void);
extern void toggle_card_selection_state(s32 value, s32 index);

/* Updates a slot's flag after four repeats of a nonzero state and returns the flag array. */
s32 *card_devkit_debounce_channel_status(void)
{
    s32 current_state;
    s32 slot_index;
    s32 one;

    current_state = card_devkit_poll_first_software_event();
    if (current_state != 0) {
        slot_index = card_dev_has_selected_channel();
        if (D_80409268[slot_index] == current_state) {
            card_channel_state_repeat_count[slot_index]++;
        } else {
            card_channel_state_repeat_count[slot_index] = 0;
        }
        D_80409268[slot_index] = current_state;
        one = 1;
        if ((current_state == one) || (current_state == 4)) {
            if (card_channel_state_repeat_count[slot_index] >= 4) {
                card_debounced_channel_flags[slot_index] = one;
            }
        } else if (card_channel_state_repeat_count[slot_index] >= 4) {
            card_debounced_channel_flags[slot_index] = 0;
        }
        toggle_card_selection_state(one, slot_index);
    }
    return card_debounced_channel_flags;
}
