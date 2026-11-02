#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/server_imports.h"


/* Marks two save slots with distinct highlight callbacks and updates the displayed selection index. */
void card_devkit_refresh_save_slot_pair_highlights(void *ptr) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == *((s32 *)ptr + 0xB)) {
            func_80404618(((void **)ptr)[i + 1], 1);
        } else if (i == *((s32 *)ptr + 0xA)) {
            card_devkit_set_window_selection_marker(((void **)ptr)[i + 1], 1);
        } else {
            card_dev_reset_object_tint(((void **)ptr)[i + 1]);
        }
    }
    card_info_set_value_and_refresh(*((s32 *)ptr + 7), *((s32 *)ptr + 0xA));
}
