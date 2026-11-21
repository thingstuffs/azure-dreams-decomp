#include "shared/object_node.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/save_slot.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/message.h"

/* Selects the object's next callback based on whether its indexed entry is active. */
void select_slot_menu_callback(void *object_state_arg)
{
    CardSaveOperationBody *object_state = object_state_arg;
    void *next_callback;
    ObjectNodeHeader *object_base;
    s32 entry_index;
    s32 entry_active;

    entry_index = object_state->entry_index;
    entry_active = card_slot_header_cache[entry_index].words[0];
    object_base = NODE_HEADER(object_state);
    if (entry_active != 0) {
        next_callback = card_dev_update_menu_input;
        object_state->saved_entry_index = entry_index;
    } else {
        object_state->completion_callback = handle_object_menu_input;
        initialize_card_message_object_with_code_7(object_base);
        next_callback = card_dev_poll_save_result_and_resume_menu_input;
    }
    (NODE_HEADER(object_state))->update_callback = next_callback;
}
