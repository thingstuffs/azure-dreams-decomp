#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"

/* Builds one of five save-slot windows per call, switching callbacks on a failed lookup or completion. */
void card_devkit_build_save_slot_windows(CardSaveOperationBody *base) {
    s32 idx;

    idx = base->window_index;
    if (idx < 5) {
        if (card_dev_load_slot_metadata(idx) != 0) {
            base->windows[idx] = init_card_window_slot_object(NODE_HEADER(base), idx);
            base->window_index = base->window_index + 1;
        } else {
            base->completion_callback = card_dev_update_save_slot_selection;
            initialize_card_message_object_with_code_0xb(NODE_HEADER(base));
            NODE_HEADER(base)->update_callback = install_pending_completion_callback;
        }
    }
    if (idx == 5) {
        NODE_HEADER(base)->update_callback = card_dev_update_save_slot_selection;
    }
}
