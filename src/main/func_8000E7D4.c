#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"







/* Updates the indexed flag after four consecutive repeats of a nonzero state. */
s32 *card_boot_debounce_card_presence(void)
{
    s32 current_state;
    s32 state_index;

    current_state = card_boot_poll_software_events();
    if (current_state != 0) {
        state_index = card_boot_has_selected_channel();
        if (card_last_presence_event[state_index] == current_state) {
            card_presence_repeats[state_index]++;
        } else {
            card_presence_repeats[state_index] = 0;
        }
        card_last_presence_event[state_index] = current_state;
        if (current_state == 1 || current_state == 4) {
            s32 *repeat_count;

            repeat_count = &card_presence_repeats[state_index];
            if (*repeat_count >= 4) {
                (*(s32 (*)[])(&card_presence_flags))[state_index] = 1;
                *repeat_count = 0;
                card_last_presence_event[state_index] = 0;
            }
        } else {
            s32 *repeat_count;

            (*(s32 (*)[])(&card_slot_completion_flags))[state_index] = 0;
            repeat_count = &card_presence_repeats[state_index];
            if (*repeat_count >= 4) {
                (*(s32 (*)[])(&card_presence_flags))[state_index] = 0;
                *repeat_count = 0;
                card_last_presence_event[state_index] = 0;
            }
        }
        card_boot_toggle_channel();
    }
    return (*(s32 (*)[])(&card_presence_flags));
}
