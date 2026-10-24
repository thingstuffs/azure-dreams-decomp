#include "common.h"
#include "frontend/card/service.h"
#include "main/data.h"

extern s32 func_804019A4(void);
extern void func_80400948(s32 value, s32 index);

/* Updates a slot's flag after four repeats of a nonzero state and returns the flag array. */
s32 *card_devkit_debounce_channel_status(void)
{
    s32 current_state;
    s32 slot_index;
    s32 one;

    current_state = card_devkit_poll_first_software_event();
    if (current_state != 0) {
        slot_index = func_804019A4();
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
        func_80400948(one, slot_index);
    }
    return card_debounced_channel_flags;
}
