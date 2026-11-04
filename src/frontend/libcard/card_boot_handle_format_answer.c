#include "shared/object_node.h"
#include "common.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Checks the object's guard field, initializes its state, and installs its dispatch table. */
void card_boot_handle_format_answer(void *object) {
    void *handler;

    if (*(s32 *)((s8 *)object + 0x3C) != 0) {
        handler = card_boot_update_card_chooser_input;
    } else {
        *(s32 *)((s8 *)object + 0x40) = 1;
        card_boot_show_formatting_progress((s8 *)object - 0x20, (s8 *)object + 0x38);
        *(s32 *)((s8 *)object + 0x38) = 1;
        handler = card_boot_wait_before_formatting_card;
    }
    ((ObjectNodeHeader *)object - 1)->update_callback = handler;
}
