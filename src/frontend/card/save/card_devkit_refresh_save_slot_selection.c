#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"

extern void save_object_value_and_set_control_fields(struct ObjectNodeHeader *object, s32 new_value);

/* Updates the five save-slot selection markers and the object displaying the selected index. */
void card_devkit_refresh_save_slot_selection(CardSaveOperationBody *menu) {
    s32 sentinel;
    s32 i;

    if (menu->slot_mode == 1) {
        sentinel = 1;
    } else {
        save_object_value_and_set_control_fields(menu->options, menu->option_index);
        sentinel = 0;
    }
    i = 0;
    while (1) {
        if (i == menu->entry_index) {
            card_devkit_set_window_selection_marker(menu->windows[i], sentinel);
        } else {
            card_dev_reset_object_tint(menu->windows[i]);
        }
        i++;
        if (i >= 5) {
            break;
        }
    }
    card_info_set_value_and_refresh(menu->information, menu->entry_index);
}
