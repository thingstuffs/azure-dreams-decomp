#include "modules/main_server_ship.h"
#include "common.h"







/* Updates the indexed flag after four consecutive repeats of a nonzero state. */
s32 *card_boot_debounce_card_presence(void)
{
    s32 current_state;
    s32 state_index;

    current_state = card_boot_poll_software_events();
    if (current_state != 0) {
        state_index = card_boot_has_selected_channel();
        if (D_80028548[state_index] == current_state) {
            D_80028540[state_index]++;
        } else {
            D_80028540[state_index] = 0;
        }
        D_80028548[state_index] = current_state;
        if (current_state == 1 || current_state == 4) {
            s32 *repeat_count;

            repeat_count = &D_80028540[state_index];
            if (*repeat_count >= 4) {
                (*(s32 (*)[])(&D_800287D8))[state_index] = 1;
                *repeat_count = 0;
                D_80028548[state_index] = 0;
            }
        } else {
            s32 *repeat_count;

            (*(s32 (*)[])(&D_80084118))[state_index] = 0;
            repeat_count = &D_80028540[state_index];
            if (*repeat_count >= 4) {
                (*(s32 (*)[])(&D_800287D8))[state_index] = 0;
                *repeat_count = 0;
                D_80028548[state_index] = 0;
            }
        }
        card_boot_toggle_channel();
    }
    return (*(s32 (*)[])(&D_800287D8));
}
