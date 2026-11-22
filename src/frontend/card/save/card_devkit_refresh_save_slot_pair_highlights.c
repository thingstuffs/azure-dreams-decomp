#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/server_imports.h"


/* Marks two save slots with distinct highlight callbacks and updates the displayed selection index. */
void card_devkit_refresh_save_slot_pair_highlights(CardSaveOperationBody *menu) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == menu->saved_entry_index) {
            func_80404618(menu->windows[i], 1);
        } else if (i == menu->entry_index) {
            card_devkit_set_window_selection_marker(menu->windows[i], 1);
        } else {
            card_dev_reset_object_tint(menu->windows[i]);
        }
    }
    card_info_set_value_and_refresh(menu->information, menu->entry_index);
}
