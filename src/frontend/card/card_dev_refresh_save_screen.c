#include "common.h"
#include "frontend/card.h"
#include "frontend/card/save_operation.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif

/* Dual symbols at the same address force load-via-v1 / store-via-at RMW
 * (retail uses separate %hi materializations, not a reused base reg). */
extern s32 D_8008DAB4_2[];

/* Processes object components and sets the object and global 0x8000 flags. */
void release_card_screen_parts(ObjectNodeHeader *node) {
    CardSaveOperationBody *body;
    s32 component_count;
    u16 object_flags;
    s32 global_flags;

    body = NODE_BODY(node);
    if (node != NULL) {
        card_dev_flag_object_dirty(body->background);
        card_dev_refresh_options_object(body->options);
        card_dev_refresh_info_object(body->information);
        for (component_count = 0; component_count < 5; component_count++) {
            card_dev_refresh_slot_window(body->windows[component_count]);
        }
        object_flags = node->flags;
        global_flags = card_ui_dirty_flags;
        object_flags |= 0x8000;
        global_flags |= 0x8000;
        node->flags = object_flags;
        D_8008DAB4_2[0] = global_flags;
    }
}
