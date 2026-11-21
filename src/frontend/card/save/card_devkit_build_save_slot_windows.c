#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/save.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"

/* Builds one of five save-slot windows per call, switching callbacks on a failed lookup or completion. */
void card_devkit_build_save_slot_windows(void *ptr) {
    void *base;
    CardDevSaveSlotWindows *slot_windows = ptr;
    s32 idx;

    base = ptr;
    idx = *(s32 *)((u8 *)base + 0x24);
    if (idx < 5) {
        if (card_dev_load_slot_metadata(idx) != 0) {
            slot_windows->windows[idx] = init_card_window_slot_object((u8 *)base - 0x20, idx);
            *(s32 *)((u8 *)base + 0x24) = *(s32 *)((u8 *)base + 0x24) + 1;
        } else {
            *(void (**)(void))((u8 *)base + 0x34) = card_dev_update_save_slot_selection;
            initialize_card_message_object_with_code_0xb(NODE_HEADER(base));
            NODE_HEADER(base)->update_callback = install_pending_completion_callback;
        }
    }
    if (idx == 5) {
        NODE_HEADER(base)->update_callback = card_dev_update_save_slot_selection;
    }
}
