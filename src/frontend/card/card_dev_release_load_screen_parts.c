#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"

/* The parts of the devkit load screen object (offsets of the server build). */
typedef struct CardDevLoadScreenParts {
    u8 pad_00[0x1E];
    u16 flags;
    void *parts[8];
} CardDevLoadScreenParts;

/*
 * Devkit-server load-screen build of release_card_screen_parts: mark the screen's object dirty, release its
 * window and slot parts and the five slot windows, then raise the 0x8000 flag on the screen and on the card UI.
 */
void card_dev_release_load_screen_parts(CardDevLoadScreenParts *screen)
{
    void **parts;
    s32 i;
    u16 flags;
    s32 dirty;

    parts = screen->parts;
    if (screen != 0) {
        card_dev_flag_object_dirty(screen->parts[0]);
        func_804059A8(screen->parts[1]);
        func_80407D38(screen->parts[2]);
        for (i = 0; i < 5; i++) {
            func_80404570(parts[i + 3]);
        }
        flags = screen->flags;
        dirty = card_ui_dirty_flags;
        flags |= 0x8000;
        dirty |= 0x8000;
        screen->flags = flags;
        card_ui_dirty_flags = dirty;
    }
}
