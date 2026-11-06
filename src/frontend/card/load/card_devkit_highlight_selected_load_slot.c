#include "common.h"
#include "frontend/card.h"
#include "frontend/card/load.h"


/* Highlights one of five load-slot windows and updates the object displaying its index. */
void card_devkit_highlight_selected_load_slot(void *ptr) {
    s32 i;

    i = 0;
    while (1) {
        if (i == *(s32 *)((u8 *)ptr + 0x2C)) {
            card_devkit_set_window_selection_marker(*(void **)((u8 *)ptr + i * 4 + 0xC), 1);
        } else {
            card_dev_reset_object_tint(*(void **)((u8 *)ptr + i * 4 + 0xC));
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    card_info_set_value_and_refresh(*(void **)((u8 *)ptr + 4), *(s32 *)((u8 *)ptr + 0x2C));
}
