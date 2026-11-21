#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "shared/object_node.h"


/* Dual symbols at the same address force load-via-v1 / store-via-at RMW
 * (retail uses separate %hi materializations, not a reused base reg). */
extern s32 D_8008DAB4_2[];

/* Node header and the components populated by the save-screen factory and slot builder. */
typedef struct CardDevSaveScreenParts {
    ObjectNodeHeader header;
    ObjectNodeHeader *background_and_slot_windows[6];
    ObjectNodeHeader *options;
    ObjectNodeHeader *info;
} CardDevSaveScreenParts;

/* Releases the save-screen components and marks the screen and card UI dirty. */
void release_card_screen_parts(void *object) {
    CardDevSaveScreenParts *screen = object;
    ObjectNodeHeader **component_cursor;
    s32 component_count;
    u16 object_flags;
    s32 global_flags;

    component_cursor = NODE_BODY(object);
    if (screen != 0) {
        card_dev_flag_object_dirty(screen->background_and_slot_windows[0]);
        card_dev_refresh_options_object(screen->options);
        card_dev_refresh_info_object(screen->info);
        for (component_count = 0; component_count < 5; component_count++) {
            card_dev_refresh_slot_window(component_cursor[component_count + 1]);
        }
        object_flags = screen->header.flags;
        global_flags = card_ui_dirty_flags;
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        screen->header.flags = object_flags;
        D_8008DAB4_2[0] = global_flags;
    }
}
