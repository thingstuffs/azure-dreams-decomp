#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"

/* Body of the devkit load screen's slot-window builder object (offsets of the server build). */
typedef struct CardDevLoadSlotScreen {
    u8 pad_00[0x0C];
    u8 *windows[5];
    u8 pad_20[0x08];
    s32 window_count;
    u8 pad_2C[0x08];
    void *state_callback;
} CardDevLoadSlotScreen;

/*
 * Devkit-server load-screen build of card_devkit_build_save_slot_windows: builds one of five slot windows per
 * call; a failed lookup shows message 0xB and switches the callbacks, the fifth call installs the highlight.
 */
void card_dev_build_load_slot_windows(CardDevLoadSlotScreen *screen)
{
    s32 index;

    index = screen->window_count;
    if (index < 5) {
        if (process_slot_record_on_lookup_success(index) != 0) {
            void *object = NODE_HEADER(screen);

            screen->windows[index] = init_card_window_slot_object(object, index);
            screen->window_count++;
        } else {
            screen->state_callback = func_80406F34;
            initialize_card_message_object_with_code_0xb(NODE_HEADER(screen));
            NODE_HEADER(screen)->update_callback = func_804069FC;
        }
    }
    if (index == 5) {
        NODE_HEADER(screen)->update_callback = func_80406F34;
    }
}
