#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/service.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/server_aliases.h"

extern void initialize_card_message_object_with_code_0x13(void *object);

/*
 * Returns to menu input when the card operation is already complete or succeeds, processing five
 * entries on success. On failure, opens message 0x13 and installs the follow-up handler.
 */
void finish_save_slot_operation(CardSaveOperationBody *menu)
{
    struct CardDevSlotWindow *entry;
    s32 entry_count;

    if (menu->dialog_answer != 0) {
        NODE_HEADER(menu)->update_callback = handle_object_menu_input;
        return;
    }

    if (card_dev_run_slot_operation(menu->entry_index) != 0) {
        entry_count = 0;
        NODE_HEADER(menu)->update_callback = handle_object_menu_input;
        do {
            entry = menu->windows[entry_count];
            entry_count++;
            card_dev_refresh_slot_window_display(entry);
        } while (entry_count < 5);
    } else {
        menu->completion_callback = handle_object_menu_input;
        initialize_card_message_object_with_code_0x13(NODE_HEADER(menu));
        NODE_HEADER(menu)->update_callback = func_80405A64;
    }

    return;
}
