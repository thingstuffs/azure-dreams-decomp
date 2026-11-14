#include "shared/object_node.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/save_slot.h"
#include "common.h"
#include "frontend/card/save.h"

extern void initialize_card_message_object_with_code_7(void *object);
extern void func_80405A64(void);
extern void process_menu_input_and_cursor_state(void);
extern CardSaveSlot card_slot_header_cache[];

/* Selects the object's next callback based on whether its indexed entry is active. */
void select_slot_menu_callback(void *object_state_arg)
{
    CardSaveOperationBody *object_state = object_state_arg;
    void (*next_callback)(void);
    ObjectNodeHeader *object_base;
    s32 entry_index;
    s32 entry_active;

    entry_index = object_state->entry_index;
    entry_active = card_slot_header_cache[entry_index].words[0];
    object_base = (ObjectNodeHeader *)object_state - 1;
    if (entry_active != 0) {
        next_callback = process_menu_input_and_cursor_state;
        object_state->saved_entry_index = entry_index;
    } else {
        object_state->completion_callback = handle_object_menu_input;
        initialize_card_message_object_with_code_7(object_base);
        next_callback = func_80405A64;
    }
    ((ObjectNodeHeader *)object_state - 1)->update_callback = next_callback;
}
