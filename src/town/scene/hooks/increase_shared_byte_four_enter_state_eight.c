#include "common.h"

extern u8 catalog_selection_state[];

/* Increase the shared byte by four and enter state eight when its low nibble clears
 * (the scroll-down partner of scroll_catalog_text_up, src/town/func_8096D1C4.c). */
void increase_shared_byte_by_four_and_enter_state_eight(void *controller) {
    u8 *state = catalog_selection_state;

    state[9] += 4;
    if (state[9] % 16 == 0) {
        *((s8 *)controller + 0xA) = 8;
    }
}
