#include "common.h"
#include "frontend/card.h"
#include "frontend/card/load.h"


/* Highlights one of five load-slot windows and updates the object displaying its index. */
void card_devkit_highlight_selected_load_slot(CardDevLoadSlotScreen *screen) {
    s32 i;

    i = 0;
    while (1) {
        if (i == screen->selection) {
            card_devkit_set_window_selection_marker(screen->windows[i], 1);
        } else {
            card_dev_reset_object_tint(screen->windows[i]);
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    card_info_set_value_and_refresh(screen->information, screen->selection);
}
