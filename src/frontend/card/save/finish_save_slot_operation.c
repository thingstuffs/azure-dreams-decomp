#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/service.h"
#include "frontend/card/save.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card.h"

typedef struct S_func_804061C4_0 {
    CardDevSaveSlotWindows slot_windows;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[8];
    void (*unk_34)(void);
    s32 unk_38;
} S_func_804061C4_0;

extern void initialize_card_message_object_with_code_0x13(void *object);

/*
 * Returns to menu input when the card operation is already complete or succeeds, processing five
 * entries on success. On failure, opens message 0x13 and installs the follow-up handler.
 */
void finish_save_slot_operation(S_func_804061C4_0 *state)
{
    struct ObjectNodeHeader *entry;
    s32 entry_count;

    if (state->unk_38 != 0) {
        NODE_HEADER(state)->update_callback = (void *)handle_object_menu_input;
        return;
    }

    if (card_dev_run_slot_operation(state->unk_28) != 0) {
        entry_count = 0;
        NODE_HEADER(state)->update_callback = (void *)handle_object_menu_input;
        do {
            entry = state->slot_windows.windows[entry_count];
            entry_count++;
            card_dev_refresh_slot_window_display(entry);
        } while (entry_count < 5);
    } else {
        state->unk_34 = handle_object_menu_input;
        initialize_card_message_object_with_code_0x13(NODE_HEADER(state));
        NODE_HEADER(state)->update_callback = (void *)func_80405A64;
    }

    return;
}
