#include "frontend/card/save_slot.h"
#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/message.h"
#include "frontend/card/save.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/save_operation.h"

extern void dispatch_operation_mode_context(void *, void *);

/* Arm the task's next callback: ready slot -> attach the sub-object, otherwise detach it. */
void select_card_slot_message(void *task)
{
    s32 one;
    ObjectNodeHeader *owner;
    s32 index;
    void (*callback)(CardSaveOperationBody *menu);

    owner = NODE_HEADER(task);
    index = *(s32 *)((u8 *)task + 0x28);
    if (card_slot_header_cache[index].fields.marker != 0) {
        one = 1;
        *(s32 *)((u8 *)task + 0x3C) = one;
        dispatch_operation_mode_context(owner, (u8 *)task + 0x40);
        callback = card_dev_save_wait_countdown;
        *(s32 *)((u8 *)task + 0x40) = one;
    } else {
        ((CardSaveOperationBody *)task)->completion_callback = handle_object_menu_input;
        initialize_card_message_object_with_code_7(owner);
        callback = card_dev_poll_save_result_and_resume_menu_input;
    }
    NODE_HEADER(task)->update_callback = callback;
}
