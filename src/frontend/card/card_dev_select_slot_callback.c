#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/message.h"
#include "shared/object_node.h"


/* Arm the task's next callback: ready slot -> attach the sub-object, otherwise detach it. */
void card_dev_select_slot_callback(CardSaveOperationBody *task) {
    ObjectNodeHeader *owner = NODE_HEADER(task);

    if (card_slot_header_cache[task->entry_index].fields.marker != 0) {
        task->completion_callback = finish_save_slot_operation;
        card_dev_show_delete_confirmation(owner, &task->dialog_answer);
        owner->update_callback = (void *)func_80405A64;
        return;
    }
    task->completion_callback = handle_object_menu_input;
    initialize_card_message_object_with_code_7(owner);

    owner->update_callback = (void *)func_80405A64;
}
