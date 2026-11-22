#include "frontend/card/save_image.h"
#include "common.h"
#include "frontend/card.h"
#include "shared/object_node.h"
#include "frontend/card/service.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/server_aliases.h"


/* Runs two card checks and processes five object entries; installs menu and message callbacks on failure. */
void commit_save_and_refresh_slots(CardSaveOperationBody *menu) {
    CardDevSaveWork *save = (CardDevSaveWork *)0x80010000;
    struct CardDevSlotWindow *value;
    s32 index;
    s32 *selected;
    ObjectNodeHeader *node_header;

    if (read_and_update_indexed_record(menu->saved_entry_index, save) != 0) {
        save->words[0] = 0;
        selected = &menu->entry_index;
        if (process_entry_with_table_value(*selected, save) != 0) {
            card_dev_no_op_save(0x80010000);
            index = 0;
            card_dev_cache_slot_summary();
            do {
                value = menu->windows[index];
                index += 1;
                card_dev_refresh_slot_window_display(value);
            } while (index < 5);
            refresh_save_slot_selection_and_resume_menu_input(menu);
            reset_card_selection_state();
            menu->state = 0;
            return;
        }
    }
    node_header = NODE_HEADER(menu);
    menu->completion_callback = handle_object_menu_input;
    initialize_card_message_object_with_code_0x10(node_header);
    node_header->update_callback = install_pending_completion_callback;
    reset_card_selection_state();
    menu->state = 0;
}
