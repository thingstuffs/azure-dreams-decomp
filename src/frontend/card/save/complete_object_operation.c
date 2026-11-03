#include "shared/object_node.h"
#include "frontend/card/save_operation.h"
#include "common.h"
#include "frontend/card/service.h"
#include "frontend/card/save.h"

extern void initialize_card_message_object_with_code_0xb(void *object_base);
extern void card_dev_no_op_save(s32 value);
extern void reset_card_selection_state(void);
extern void card_dev_commit_pending_value(void);
extern void set_object_state_and_select_action(void);

// Selects the next callback based on the operation result and clears the context's state field.
void complete_object_operation(void *context_arg)
{
    CardSaveOperationBody *context = context_arg;
    void (*next_callback)(void);
    ObjectNodeHeader *object_base;
    s32 operation_result;

    operation_result = read_and_update_indexed_record(context->entry_index, 0x80010000);
    object_base = (ObjectNodeHeader *)context - 1;
    if (operation_result == 0) {
        context->completion_callback = handle_object_menu_input;
        initialize_card_message_object_with_code_0xb(object_base);
        next_callback = card_dev_commit_pending_value;
    } else {
        card_dev_no_op_save(0x80010000);
        next_callback = set_object_state_and_select_action;
    }
    ((ObjectNodeHeader *)context - 1)->update_callback = next_callback;
    reset_card_selection_state();
    context->state = 0;
}
