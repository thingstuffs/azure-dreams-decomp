#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "shared/object_node.h"

extern u8 card_slot_header_cache[];
extern void initialize_card_message_object_with_code_7(void *task);
extern void func_80405A64(void);

/* Arm the task's next callback: ready slot -> attach the sub-object, otherwise detach it. */
void card_dev_select_slot_callback(u8 *task) {
    ObjectNodeHeader *owner = NODE_HEADER(task);

    if (*(s32 *)(card_slot_header_cache + (*(u32 *)(task + 0x28) << 7)) != 0) {
        *(void **)(task + 0x34) = (void *)process_five_object_entries;
        card_dev_show_delete_confirmation(owner, task + 0x38);
        *(void **)(task - 0x10) = (void *)func_80405A64;
        return;
    }
    *(void **)(task + 0x34) = (void *)handle_object_menu_input;
    initialize_card_message_object_with_code_7(owner);

    *(void **)(task - 0x10) = (void *)func_80405A64;
}
