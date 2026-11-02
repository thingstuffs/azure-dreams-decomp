#include "common.h"
#include "town/menu.h"
#include "town/data.h"

/* Decrease the shared byte by four and enter state eight when its low nibble clears. */
void scroll_catalog_text_up(void *controller) {
    u8 *state = catalog_selection_state;

    state[9] -= 4;
    if (state[9] % 16 == 0) {
        *((s8 *)controller + 0xA) = 8;
    }
}
