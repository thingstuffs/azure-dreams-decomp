#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "frontend/card/server_aliases.h"

/*
 * Devkit-server load-screen build of card_devkit_build_save_slot_windows: builds one of five slot windows per
 * call; a failed lookup shows message 0xB and switches the callbacks, the fifth call installs the highlight.
 */
void card_dev_build_load_slot_windows(CardDevLoadSlotScreen *screen)
{
    s32 index;

    index = screen->window_count;
    if (index < 5) {
        if (card_dev_load_slot_metadata(index) != 0) {
            ObjectNodeHeader *object = NODE_HEADER(screen);

            screen->windows[index] = init_card_window_slot_object(object, index);
            screen->window_count++;
        } else {
            screen->state_callback = card_dev_update_load_slot_highlight;
            card_dev_show_load_failure_notice(NODE_HEADER(screen));
            NODE_HEADER(screen)->update_callback = install_pending_load_completion_callback;
        }
    }
    if (index == 5) {
        NODE_HEADER(screen)->update_callback = card_dev_update_load_slot_highlight;
    }
}
