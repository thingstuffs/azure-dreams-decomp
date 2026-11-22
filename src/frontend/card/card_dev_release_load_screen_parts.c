#include "common.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "frontend/card/server_aliases.h"

/*
 * Devkit-server load-screen build of release_card_screen_parts: mark the screen's object dirty, release its
 * window and slot parts and the five slot windows, then raise the 0x8000 flag on the screen and on the card UI.
 */
void card_dev_release_load_screen_parts(CardDevLoadNode *screen)
{
    CardDevLoadSlotScreen *body;
    s32 i;
    u16 flags;
    s32 dirty;

    body = &screen->body;
    if (screen != 0) {
        card_dev_flag_object_dirty(body->background);
        card_dev_refresh_info_object(body->information);
        card_dev_refresh_sme_object(body->slot_display);
        for (i = 0; i < 5; i++) {
            card_dev_refresh_slot_window(body->windows[i]);
        }
        flags = screen->node.flags;
        dirty = card_ui_dirty_flags;
        flags |= 0x8000;
        dirty |= 0x8000;
        screen->node.flags = flags;
        card_ui_dirty_flags = dirty;
    }
}
